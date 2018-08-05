#ifndef SHOOT_H_INCLUDED
#define SHOOT_H_INCLUDED

int intro(SDL_Surface *screen);
int shoot(SDL_Surface *screen, int tempsPartie, SDL_Rect *positionMire, int difficulty);
Uint32 choisirCible(Uint32 intervalle, void *param);
int tirCorrect(SDL_Surface *screen, SDL_Surface *cible, SDL_Rect *positionCibleMIN, SDL_Event *event);
int pause(int* quitScreen);




#endif // SHOOT_H_INCLUDED
