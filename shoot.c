//#include <stdlib.h>
//#include <stdio.h>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <time.h>
//#include <SDL_ttf.h>
//#include <fmodex\fmod.h>
//#include "struct.h"
//#include "constantes.h"
//#include "shoot.h"
//
//
//
//int shoot(SDL_Surface *screen, int tempsPartie, SDL_Rect *positionMire, int difficulty)
//{
//    SDL_Color couleurScore = {255, 242, 0};
//    SDL_Surface *background = NULL, *mire = NULL, *scoreSurface = NULL, *menu = NULL, *tempsRestantSurface = NULL, *barreDeSon = NULL;
//    SDL_Event event;
//    SDL_TimerID timer;
//    SHOOT_Image cible;
//    cible.difficulty = difficulty;
//    SDL_Rect position;
//    TTF_Font *police = NULL;
//    int continuer = 1, quitScreen = 0, revenirMenu = 0;
//    int score = 0;
//    int clicGaucheEnCours = 0, touche_P_EnCours = 0;
//    int tempsDebut, tempsFin, tempsMisEnPause = 0;
//    int curseurVisible = 0;
//    char scoreTexte[20] = {0}, tempsRestant[20] = {0};
//    int i;
//    int nombreDeBarresDeSon = 10;
//
//    /* Gestion du son */
//    FMOD_SYSTEM *system;
//    FMOD_SOUND *gunShoot = NULL, *music = NULL, *success = NULL;
//
//    FMOD_System_Create(&system);
//    FMOD_System_Init(system, 4, FMOD_INIT_NORMAL, NULL);
//
//    FMOD_System_CreateSound(system, "data\\audio\\gun.wav", FMOD_CREATESAMPLE, NULL, &gunShoot);
//    FMOD_System_CreateSound(system, "data\\audio\\bourne.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &music);
//    FMOD_System_CreateSound(system, "data\\audio\\success.wav", FMOD_CREATESAMPLE, NULL, &success);
//
//    FMOD_CHANNELGROUP *channel;
//    FMOD_System_GetMasterChannelGroup(system, &channel);
//
//    FMOD_Sound_SetLoopCount(music, -1);
//    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, music, 0, NULL);
//
//    /* Surfaces et texte */
//    police = TTF_OpenFont("data\\police.ttf", 40);
//    mire  =  IMG_Load("data\\images\\mire.bmp");
//                SDL_SetColorKey(mire, SDL_SRCCOLORKEY, SDL_MapRGB(mire->format, 0, 0, 255));
//
//
//    /* Variables propres à l'intro */
//    SDL_Surface *fond = NULL;
//    int tempsIntro = 3000;
//
//    tempsDebut = SDL_GetTicks();
//    fond = IMG_Load("data\\images\\startShoot.bmp");
//
///* INTRO */
//    while (tempsIntro > 0 && continuer)
//    {
//        tempsFin = SDL_GetTicks();
//        tempsIntro = 3 - ((tempsFin - tempsDebut) / 1000);
//        sprintf(tempsRestant, "%d", tempsIntro);
//        tempsRestantSurface = TTF_RenderText_Blended(police, tempsRestant, couleurScore);
//
//        position.x = 0;
//        position.y = 0;
//        SDL_BlitSurface(fond, NULL, screen, &position);
//        position.x = screen->w / 2 - tempsRestantSurface->w / 2;
//        position.y = screen->h / 2 - tempsRestantSurface->h / 2;
//        SDL_BlitSurface(tempsRestantSurface, NULL, screen, &position);
//        SDL_BlitSurface(mire, NULL, screen, positionMire);
//        SDL_Flip(screen);
//
//        SDL_PollEvent(&event);
//        switch (event.type)
//        {
//            case SDL_QUIT:
//                quitScreen = 1;
//                continuer = 0;
//                break;
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.sym)
//                {
//                    case SDLK_ESCAPE:
//                            FMOD_Sound_Release(success);
//                            FMOD_Sound_Release(music);
//                            FMOD_Sound_Release(gunShoot);
//                            FMOD_System_Close(system);
//                            FMOD_System_Release(system);
//                            SDL_FreeSurface(fond);
//                            SDL_FreeSurface(scoreSurface);
//                            SDL_FreeSurface(tempsRestantSurface);
//                            SDL_FreeSurface(mire);
//                            TTF_CloseFont(police);
//                            return 0;
//                        break;
//                    case SDLK_RETURN:
//                        continuer = 0;
//                        break;
//                }
//                break;
//            case SDL_MOUSEMOTION:
//                positionMire->x = event.motion.x - (mire->w / 2);
//                positionMire->y = event.motion.y - (mire->h / 2);
//                break;
//            case SDL_MOUSEBUTTONDOWN:
//                if (event.button.button == SDL_BUTTON_LEFT)
//                {
//                    if (clicGaucheEnCours == 0)
//                    {
//                        clicGaucheEnCours = 1;
//                      //  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, gunShoot, 0, NULL);
//                        continuer = 0;
//                    }
//
//                }
//
//                break;
//        }
//
//
//    }
//
///* JEU PRINCIPAL */
//    continuer = 1;
//    clicGaucheEnCours = 0;
//    sprintf(tempsRestant, "Temps restant: %d", tempsPartie - tempsFin);
//    sprintf(scoreTexte, "Score: %d", score);
//    tempsRestantSurface =   TTF_RenderText_Blended(police, tempsRestant, couleurScore);
//    scoreSurface =          TTF_RenderText_Blended(police, scoreTexte, couleurScore);
//    background =    IMG_Load("data\\images\\foret.jpg");
//    menu =          IMG_Load("data\\images\\menu.bmp");
//    cible.surface = IMG_Load("data\\images\\vide.bmp");
//                        /* Transparence avec le bleu */
//                        SDL_SetColorKey(cible.surface, SDL_SRCCOLORKEY, SDL_MapRGB(cible.surface->format, 0, 0, 255));
//
//    barreDeSon = IMG_Load("data\\images\\jaune.bmp");
//
//    tempsDebut = SDL_GetTicks();
//
//    timer = SDL_AddTimer(1000, choisirCible, &cible);
//    while (continuer && !quitScreen && !revenirMenu)
//    {
//        tempsFin = SDL_GetTicks();
//        sprintf(tempsRestant, "%d", (tempsPartie + tempsDebut - tempsFin + tempsMisEnPause) / 1000 + 1);
//        tempsRestantSurface =   TTF_RenderText_Blended(police, tempsRestant, couleurScore);
//        if (tempsFin - tempsDebut > tempsPartie + tempsMisEnPause)
//            continuer = 0;
//
//        position.x = 0;
//        position.y = 100;
//            SDL_BlitSurface(background, NULL, screen, &position);
//        position.y = 0;
//            SDL_BlitSurface(menu, NULL, screen, &position);
//        position.x = (menu->h / 2) - (scoreSurface->h / 2);
//        position.y = position.x;
//            SDL_BlitSurface(scoreSurface, NULL, screen, &position);
//        position.x = 600;
//            SDL_BlitSurface(tempsRestantSurface, NULL, screen, &position);
//        SDL_BlitSurface(cible.surface, NULL, screen, &(cible.position));
//        position.x = 350;
//        position.y = MENU_H / 2 - barreDeSon->h / 2;
//        for (i = 0; i < nombreDeBarresDeSon; i++) // Barres de son.
//        {
//            SDL_BlitSurface(barreDeSon, NULL, screen, &position);
//            position.x += 10;
//        }
//
//        if (positionMire->y + mire->h / 2 > MENU_H)
//        {
//            if (curseurVisible)
//                SDL_ShowCursor(SDL_DISABLE);
//            curseurVisible = 0;
//            SDL_BlitSurface(mire, NULL, screen, positionMire);
//
//        }
//        else
//        {
//            if (!curseurVisible)
//                SDL_ShowCursor(SDL_ENABLE);
//            curseurVisible = 1;
//        }
//
//        SDL_Flip(screen);
//
//        SDL_PollEvent(&event);
//        switch (event.type)
//        {
//            case SDL_QUIT:
//                continuer = 0;
//                quitScreen = 1;
//                break;
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.sym)
//                {
//                    case SDLK_ESCAPE:
//                        continuer = 0;
//                        break;
//                    case SDLK_p:
//                        if (!touche_P_EnCours)
//                        {
//                            tempsMisEnPause = tempsMisEnPause + pause(&quitScreen); // Pause retourne le temps écoulé au cours de la fonction pause().
//                        }
//
//                        touche_P_EnCours = 1;
//                        break;
//                }
//                break;
//            case SDL_KEYUP:
//                switch (event.key.keysym.sym)
//                {
//                    case SDLK_p:
//                        touche_P_EnCours = 0;
//                        break;
//                }
//                break;
//            case SDL_MOUSEMOTION:
//                positionMire->x = event.motion.x - (mire->w / 2);
//                positionMire->y = event.motion.y - (mire->h / 2);
//                break;
//            case SDL_MOUSEBUTTONDOWN:
//                if (event.button.button == SDL_BUTTON_LEFT)
//                {
//                    if (event.button.y  < MENU_H) // Si le clic est dans la zone du menu.
//                    {
//                        if (event.button.x > 350)
//                        {
//                            if (event.button.x < 360)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.0);
//                                nombreDeBarresDeSon = 0;
//                            }
//                            else if (event.button.x < 370)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.1);
//                                nombreDeBarresDeSon = 1;
//                            }
//                            else if (event.button.x < 380)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.2);
//                                nombreDeBarresDeSon = 2;
//                            }
//                            else if (event.button.x < 390)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.3);
//                                nombreDeBarresDeSon = 3;
//                            }
//                            else if (event.button.x < 400)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.4);
//                                nombreDeBarresDeSon = 4;
//                            }
//                            else if (event.button.x < 410)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.5);
//                                nombreDeBarresDeSon = 5;
//                            }
//                            else if (event.button.x < 420)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.6);
//                                nombreDeBarresDeSon = 6;
//                            }
//                            else if (event.button.x < 430)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.7);
//                                nombreDeBarresDeSon = 7;
//                            }
//                            else if (event.button.x < 440)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.8);
//                                nombreDeBarresDeSon = 8;
//                            }
//                            else if (event.button.x < 450)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 0.9);
//                                nombreDeBarresDeSon = 9;
//                            }
//                            else if (event.button.x < 500)
//                            {
//                                FMOD_ChannelGroup_SetVolume(channel, 1.0);
//                                nombreDeBarresDeSon = 10;
//                            }
//                        }
//                    }
//                    if (clicGaucheEnCours == 0)
//                    {
//                        clicGaucheEnCours = 1;
//                        if (!curseurVisible)
//                            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, gunShoot, 0, NULL);
//                        if (tirCorrect(screen, cible.surface, &(cible.position), &event)) // tirCorrect() retourne 1 si le tir est bon.
//                        {
//                            if (cible.id == ZOZOR)
//                                score += 10;
//                            else if (cible.id == VIDE)
//                                score -= 5;
//                            else
//                                score -= 25;
//
//                            cible.surface = IMG_Load("data\\images\\vide.bmp");
//                            /* Transparence avec le bleu */
//                                SDL_SetColorKey(cible.surface, SDL_SRCCOLORKEY, SDL_MapRGB(cible.surface->format, 0, 0, 255));
//                            cible.id = VIDE;
//                        }
//                        else
//                        {
//                            score -= 5;
//                        }
//                        if (score < 0)  // Empêche les scores négatifs.
//                            score = 0;
//                        sprintf(scoreTexte, "Score: %d", score);
//                        scoreSurface =  TTF_RenderText_Blended(police, scoreTexte, couleurScore);
//                    }
//                }
//                break;
//            case SDL_MOUSEBUTTONUP:
//                if (event.button.button == SDL_BUTTON_LEFT)
//                {
//                    clicGaucheEnCours = 0;
//                }
//                break;
//        }
//
//    }
//    SDL_RemoveTimer(timer);
//
///* TIME'S UP! */
//    fprintf(stderr, "Coordonees de la souris: %d, %d\n", positionMire->x, positionMire->y);
//    if (!quitScreen && !revenirMenu)
//    {
//        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, success, 0, NULL);
//        fond = IMG_Load("data\\images\\endShoot.bmp");
//        continuer = 1;
//        while (continuer)
//        {
//            position.x = 0;
//            position.y = 0;
//            SDL_BlitSurface(fond, NULL, screen, &position);
//            position.x = screen->w / 2 - scoreSurface->w / 2;
//            position.y = screen->h / 2 + scoreSurface->h / 2; // c'est décalé et c'est voulu.
//            SDL_BlitSurface(scoreSurface, NULL, screen, &position);
//            SDL_BlitSurface(mire, NULL, screen, positionMire);
//            SDL_Flip(screen);
//
//            SDL_WaitEvent(&event);
//            switch (event.type)
//            {
//                case SDL_QUIT:
//                    continuer = 0;
//                    quitScreen = 1;
//                    break;
//                case SDL_KEYDOWN:
//                    switch (event.key.keysym.sym)
//                    {
//                        case SDLK_ESCAPE:
//                            continuer = 0;
//                            break;
//                        case SDLK_RETURN:
//                            continuer = 0;
//                            break;
//                    }
//                    break;
//                case SDL_MOUSEMOTION:
//                    positionMire->x = event.motion.x - (mire->w / 2);
//                    positionMire->y = event.motion.y - (mire->h / 2);
//                    break;
//                case SDL_MOUSEBUTTONDOWN:
//                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, gunShoot, 0, NULL);
//                    break;
//            }
//
//
//        }
//    }
//
//    if (calculHighscore(tempsPartie, difficulty) < score)
//    {
//        /* Inscrit le high score si cas échant */
//        int i, t = tempsPartie / 10000; // le temps de la partie est en dizaines de secondes.
//        char c, chaine[50] = {0};
//        int tableauDesScores[2000] = {0};
//        /* Load le High Score */
//        FILE* fichierHS = NULL;
//        int highscorePresent;
//        fichierHS = fopen("data\\hs.txt", "r+");
//        if (fichierHS == NULL)
//        {
//            fprintf(stderr, "Impossible d'ouvrir le fichier High_Score.txt");
//            exit(EXIT_FAILURE);
//        }
//
//        rewind(fichierHS);
//        for (i = 0; i < 2000; i++)  // On copie le fichier dans un tableau
//        {
//            fgets(chaine, 50, fichierHS);
//            tableauDesScores[i] = atoi(chaine);
//            i++;
//        }
//
//        tableauDesScores[4 * t + difficulty - 4] = score; //Important, c'est la modification qu'on apporte. (remplacement des scores)
//
//        rewind(fichierHS);
//        for (i = 0; i < 2000; i++) // On copie le tableau modifié dans le fichier.
//        {
//            sprintf(chaine, "%d\n", tableauDesScores[i]);
//            fputs(chaine, fichierHS);
//        }
//        fclose(fichierHS);
//    }
//
//    FMOD_Sound_Release(success);
//    FMOD_Sound_Release(music);
//    FMOD_Sound_Release(gunShoot);
//    FMOD_System_Close(system);
//    FMOD_System_Release(system);
//    SDL_FreeSurface(barreDeSon);
//    SDL_RemoveTimer(timer);
//    SDL_FreeSurface(fond);
//    SDL_FreeSurface(scoreSurface);
//    SDL_FreeSurface(tempsRestantSurface);
//    SDL_FreeSurface(background);
//    SDL_FreeSurface(mire);
//    SDL_FreeSurface(cible.surface);
//    TTF_CloseFont(police);
//
//    return quitScreen;
//}
//
//int pause(int* quitScreen)
//{
//    SDL_Event event;
//    int continuer = 1;
//    int tempsDebut;
//
//    tempsDebut = SDL_GetTicks();
//    while (continuer)
//    {
//        SDL_WaitEvent(&event);
//        switch (event.type)
//        {
//            case SDL_QUIT:
//                continuer = 0;
//                *quitScreen = 1;
//                break;
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.sym)
//                {
//                    case SDLK_p:
//                        continuer = 0;
//                        break;
//                }
//                break;
//        }
//
//    }
//    return SDL_GetTicks() - tempsDebut;
//}
//
//
//Uint32 choisirCible(Uint32 intervalle, void *param)
//{
//    srand(time(NULL));
//    SHOOT_Image *cible = param;
//    SDL_TimerID timer;
//    intervalle = 2000 - 200 * cible->difficulty; // Intervalle variant selon la difficulté, de 1.4 à 2 secondes.
//
//    int choix;
//    choix = (rand() % 20) + 1;
//
//    switch (choix)
//    {
//        case 17:
//            cible->surface = IMG_Load("data\\images\\1.bmp");
//            cible->id = NICOLAS;
//            break;
//        case 18:
//            cible->surface = IMG_Load("data\\images\\2.bmp");
//            cible->id = XAVIER;
//            break;
//        case 19:
//            cible->surface = IMG_Load("data\\images\\3.bmp");
//            cible->id = THOMAS;
//            break;
//        case 20:
//            cible->surface = IMG_Load("data\\images\\4.bmp");
//            cible->id = cible->id = LAURENT;
//            break;
//        default:
//            cible->surface = IMG_Load("data\\images\\zozor.bmp");
//            cible->id = ZOZOR;
//            break;
//    }
//
//    /* Transparence avec le bleu */
//    SDL_SetColorKey(cible->surface, SDL_SRCCOLORKEY, SDL_MapRGB(cible->surface->format, 0, 0, 255));
//
//    cible->position.x = (rand() % (WINDOW_W - cible->surface->w) );
//    cible->position.y = (rand() % (WINDOW_H - cible->surface->h - MENU_H) + MENU_H); // le minimum correspond à la hauteur du menu.
//
//    /* Enlève la cible au bout d'un certain temps */
//    SDL_Delay(1000 - (250 * cible->difficulty)); // difficulty = 0, 1, 2, ou 3.
//    cible->surface = IMG_Load("data\\images\\vide.bmp");
//       /* Transparence avec le bleu */
//        SDL_SetColorKey(cible->surface, SDL_SRCCOLORKEY, SDL_MapRGB(cible->surface->format, 0, 0, 255));
//    cible->id = VIDE;
//
//    return intervalle; // Intervalle aléatoire de 3 à 6 secondes.
//}
//
//
//int tirCorrect(SDL_Surface *screen, SDL_Surface *cible, SDL_Rect *positionCibleMIN, SDL_Event *event)
//{
//    SDL_Rect positionCibleMAX;
//
//    positionCibleMAX.x = positionCibleMIN->x + cible->w;
//    positionCibleMAX.y = positionCibleMIN->y + cible->h;
//
//    if (event->motion.x < positionCibleMAX.x && event->motion.x > positionCibleMIN->x &&
//        event->motion.y < positionCibleMAX.y && event->motion.y > positionCibleMIN->y)
//        return 1;
//    else
//        return 0;
//}
