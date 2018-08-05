#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fmodex/fmod.h>
#include "struct.h"
#include "constantes.h"

int initParam(SHOOT_Param *param)
{
    param->difficulty = MODERATE;
    param->tempsPartie = 60000;
    param->highscore = calculHighscore(param->tempsPartie, param->difficulty);
}

void changerDifficulty(SHOOT_Param *param, SHOOT_Texte *txt)
{
    param->difficulty = (param->difficulty + 1) % 4;
    switch (param->difficulty)
    {
        case EASY:
            sprintf(txt->difficulty, "Difficulty: Easy");
            break;
        case MODERATE:
            sprintf(txt->difficulty, "Difficulty: Moderate");
            break;
        case HARD:
            sprintf(txt->difficulty, "Difficulty: Hard");
            break;
        case IMPOSSIBLE:
            sprintf(txt->difficulty, "Difficulty: Impossible");
            break;
    }

}

int calculHighscore(int tempsPartie, int difficulty)
{
    int t = tempsPartie / 10000, compteur; // le temps de la partie est en dizaines de secondes.
    char chaine[50] = {0};
    /* Load le High Score */
    FILE* fichierHS = NULL;
    int highscore;
    fichierHS = fopen("data\\hs.txt", "r");
    if (fichierHS == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier High_Score.txt");
        exit(EXIT_FAILURE);
    }

    rewind(fichierHS);
    compteur = 0;
    while (compteur < (4 * t) + difficulty - 3)
    {
        fgets(chaine, 50, fichierHS);
        compteur++;
    }
    highscore = atoi(chaine);
    fclose(fichierHS);
    return highscore;
}

int fullscreen()
{
    FILE* fichier = NULL;
    char c;

    fichier = fopen("OPTIONS.txt", "r");
    if (fichier == NULL)
    {
        fprintf(stderr, "Le fichier OPTIONS.txt est introuvable.");
        exit(0);
    }

    while (fgetc(fichier) != '=');

    while (fgetc(fichier) != ' ');
    c = fgetc(fichier);

    if (c == '1')
        return 1;
    else
        return 0;

}

