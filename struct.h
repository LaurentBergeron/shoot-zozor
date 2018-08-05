#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct SHOOT_Param SHOOT_Param;
struct SHOOT_Param
{
    int difficulty;
    int tempsPartie;
    int highscore;
};

typedef struct SHOOT_Audio SHOOT_Audio;
struct SHOOT_Audio
{
    FMOD_SYSTEM *system;
    FMOD_RESULT result;
    FMOD_SOUND *gunShoot;
    FMOD_SOUND *music;
    FMOD_CHANNEL *channel_menu;
    int sonActive;
};

typedef struct SHOOT_Cible SHOOT_Cible;
struct SHOOT_Cible
{
    SDL_Surface *img_Cible;
    SDL_Rect *pos_Cible;
    int id;
};

typedef struct SHOOT_Surface SHOOT_Surface;
struct SHOOT_Surface
{
    SDL_Surface *background;
    SDL_Surface *mire;
    SDL_Surface *icone;
    SDL_Surface *son;
    SDL_Surface *shoot;
    SDL_Surface *highScore;
    SDL_Surface *temps;
    SDL_Surface *difficulty;
    SHOOT_Cible *cible_1;
    SHOOT_Cible *cible_2;
    SHOOT_Cible *cible_3;
};

typedef struct SHOOT_Texte SHOOT_Texte;
struct SHOOT_Texte
{
    TTF_Font *police;
    char temps[30];
    char difficulty[30];
    char highscore[30];
};


typedef struct SHOOT_Video SHOOT_Video;
struct SHOOT_Video
{
    SDL_Surface *screen;
    SHOOT_Surface img;
    SHOOT_Texte txt;
    SDL_Rect pos_Mire;
    SDL_Color couleur;
};

#endif // STRUCT_H_INCLUDED
