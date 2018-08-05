#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED


int initParam(SHOOT_Param *param);
void changerDifficulty(SHOOT_Param *param, SHOOT_Texte *txt);
int calculHighscore(int tempsPartie, int difficulty);
int fullscreen();

#endif // OPTIONS_H_INCLUDED
