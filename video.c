#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <fmodex/fmod.h>
#include <time.h>
#include "constantes.h"
#include "struct.h"
#include "video.h"
#include "audio.h"

int initVideo(SHOOT_Video *video)
{
        // Initialise la SDL vidéo.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "Impossible d'initialiser la SDL vidéo: %s\n", SDL_GetError() );
        return -1;
    }

    if (fullscreen())
        video->screen = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    else
        video->screen = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!video->screen)
    {
        fprintf(stderr, "Impossible d'initialiser le mode vidéo %dx%d %s\n", WINDOW_W, WINDOW_H, SDL_GetError() );
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() < 0)
    {
        fprintf(stderr, "Impossible d'initialiser TTF: %s\n", TTF_GetError() );
        return -1;
    }

    if (initTxt(&video->txt) < 0)
        return -1;

    video->img->background = IMG_Load("data\\images\\mainScreen.bmp");
    if (!video->img->background)
    {
        fprintf(stderr, "Impossible d'ouvrir l'image mainScreen.bmp : %s.\n", SDL_GetError() );
        return -1;
    }

    video->img->mire = IMG_Load("data\\images\\mire.bmp");
    SDL_SetColorKey(video->img->mire, SDL_SRCCOLORKEY, SDL_MapRGB(video->img->mire->format, 0, 0, 255));
    if (!video->img->mire)
    {
        fprintf(stderr, "Impossible d'ouvrir l'image mire.bmp : %s.\n", SDL_GetError() );
        return -1;
    }

    video->img->son = IMG_Load("data\\images\\son_ON.bmp");
    SDL_SetColorKey(video->img->son, SDL_SRCCOLORKEY, SDL_MapRGB(video->img->son->format, 0, 0, 255));
    if (!video->img->son)
    {
        fprintf(stderr, "Impossible d'ouvrir l'image son_ON.bmp : %s.\n", SDL_GetError() );
        return -1;
    }

    video->img->shoot = TTF_RenderText_Blended(video->txt->police, "Start Shooting!", couleur);
    if (!video->img->shoot)
    {
        fprintf(stderr, "Le rendu de texte a échoué : %s.\n", TTF_GetError() );
        return -1;
    }

    video->couleur = {237, 28, 36};

    fprintf(stdout, "Initialisation vidéo réussie.\n");

    /*
        INITIALISATION TEXTE
    */
    video->txt->police = TTF_OpenFont("data\\police.ttf", 42);
    if (!video->txt->police)
    {
        fprintf(stderr, "Impossible d'ouvrir la police: %s\n", TTF_GetError() );
        return -1;
    }
    sprintf(video->txt->difficulty, "Difficulty: Easy");

    fprintf(stdout, "Initialisation texte réussie.\n");

    return 0;
}

int initTxt(SHOOT_Texte *txt)
{

}


int quitVideo(SHOOT_Video *video)
{
    TTF_CloseFont(video->txt->police);
    SDL_FreeSurface(video->img->background);
    SDL_FreeSurface(video->img->mire);
    SDL_FreeSurface(video->img->highScore);
    SDL_FreeSurface(video->img->difficulty);
    SDL_FreeSurface(video->img->shoot);
    SDL_FreeSurface(video->img->temps);
    SDL_FreeSurface(video->img->son);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

