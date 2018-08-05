#include <stdlib.h>
#include <stdio.h>
#include <SDL\SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fmodex\fmod.h>
#include "struct.h"
#include "constantes.h"
#include "audio.h"
#include "video.h"
#include "options.h"
#include "shoot.h"


int main (int argc, char* argv[])
{
    SHOOT_Video video;
    SHOOT_Audio audio;
    SHOOT_Param param;
    SDL_Rect pos;
    SDL_Event event;
    int continuer = 1;

    initVideo(&video);
    initAudio(&audio);
    initParam(&param);

    /* Gestion du son */

    FMOD_System_PlaySound(audio.system, FMOD_CHANNEL_FREE, audio.music, 0, NULL);

    SDL_WM_SetCaption("Shoot Zozor", NULL);

    while (continuer)
    {

        pos.x = 0;
        pos.y = 0;
            SDL_BlitSurface(video.img.background, NULL, video.screen, &pos);
        pos.x = 200;
        pos.y = 250;
            video.img.difficulty = TTF_RenderText_Blended(video.txt.police, video.txt.difficulty, video.couleur);
            SDL_BlitSurface(video.img.difficulty, NULL, video.screen, &pos);
        pos.y = 325;
            sprintf(video.txt.temps, "Time: <- %d ->", param.tempsPartie / 1000);
            video.img.temps = TTF_RenderText_Blended(video.txt.police, video.txt.temps, video.couleur);
            SDL_BlitSurface(video.img.temps, NULL, video.screen, &pos);
        pos.y = 400;
            SDL_BlitSurface(video.img.shoot, NULL, video.screen, &pos);
        pos.x = 25;
        pos.y = WINDOW_H - 75;
            sprintf(video.txt.highscore, "High Score: %d", param.highscore);
            video.img.highScore = TTF_RenderText_Blended(video.txt.police, video.txt.highscore, video.couleur);
            SDL_BlitSurface(video.img.highScore, NULL, video.screen, &pos);
        pos.x = WINDOW_W - 50;
        pos.y = WINDOW_H - 50;
            SDL_BlitSurface(video.img.son, NULL, video.screen, &pos);
        SDL_Flip(video.screen);
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                video.pos_Mire.x = event.motion.x - (video.img.mire->w / 2);
                video.pos_Mire.y = event.motion.y - (video.img.mire->h / 2);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) // Calcule le high score à chaque clic car il est sujet à changement (à la fin du if).
                {
                    if (event.button.x > WINDOW_W - 50 && event.button.y > WINDOW_H - 50)   // modifier volume.
                    {

                        if (audio.sonActive)
                        {
                            audio.sonActive = 0;
                            FMOD_Channel_SetVolume(audio.channel_menu, 0.0);
                            video.img.son = IMG_Load("data\\images\\son_OFF.bmp");
                            SDL_SetColorKey(video.img.son, SDL_SRCCOLORKEY, SDL_MapRGB(video.img.son->format, 0, 0, 255));
                        }
                        else if (!audio.sonActive)
                        {
                            audio.sonActive = 1;
                            FMOD_Channel_SetVolume(audio.channel_menu, 1.0);
                            video.img.son = IMG_Load("data\\images\\son_ON.bmp");
                            SDL_SetColorKey(video.img.son, SDL_SRCCOLORKEY, SDL_MapRGB(video.img.son->format, 0, 0, 255));
                        }
                    }
                    if (event.button.x > 200) // Gère l'emplacement des clics pour les surfaces.
                    {
                        /* Surface Shoot (Jeu principal) */
                        if (event.button.x < 200 + video.img.shoot->w && event.button.y > 400 && event.button.y < 400 + video.img.shoot->h)
                        {
                            FMOD_Channel_Stop(audio.channel_menu);
                            FMOD_System_PlaySound(audio.system, FMOD_CHANNEL_FREE, audio.gunShoot, 0, NULL);
                            SDL_ShowCursor(SDL_DISABLE);
                            if (shoot(video.screen, param.tempsPartie, &video.pos_Mire, param.difficulty))
                                continuer = 0;
                            SDL_ShowCursor(SDL_ENABLE);
                            FMOD_System_PlaySound(audio.system, FMOD_CHANNEL_FREE, audio.music, 0, NULL);
                        }

                        /* Surface Difficulty */
                        if (event.button.x < 200 + video.img.difficulty->w && event.button.y > 250 && event.button.y < 250 + video.img.difficulty->h)
                        {
                            changerDifficulty(&param, &video.txt);

                        }

                        /* Surface Changer le temps */
                        if (event.button.y > 325 && event.button.y < 325 + video.img.temps->h)
                        {
                            if (event.button.x < 350 && event.button.x > 320)
                            {
                                param.tempsPartie -= 15000;
                            }
                            if (event.button.x > 170 + video.img.temps->w && event.button.x < 200 + video.img.temps->w)
                            {
                                param.tempsPartie += 15000;
                            }
                            if (param.tempsPartie < 30000)
                                param.tempsPartie = 30000;
                            if (param.tempsPartie > 600000) // Temps maximum.
                                param.tempsPartie = 600000;

                        }
                    }
                    param.highscore = calculHighscore(param.tempsPartie, param.difficulty);
                }
                break;
            default:
                break;
        }

    }



    return EXIT_SUCCESS;
}
