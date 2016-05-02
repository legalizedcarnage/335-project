#ifndef MIGUEL_H
#define MIGUEL_H
//intialize
void knife(Game *game);
void crowbar(Game *game);
void pistol(Game *game);
void rifle(Game *game);
void shield(Game *game);
void shotgun(Game *game);
//makes particles for each weapon
// shotgun 3 bullets, rifle alot straight, pistol one
// mele no particle
void makeKnife(Game *game, int x, int y); 
void makeCrowbar(Game *game, int x, int y); 
void makePistol(Game *game, int x, int y); 
void makeRifle(Game *game, int x, int y); 
void makeShield(Game *game, int x, int y); 
void makeShotgun(Game *game, int x, int y);
//render weapon
void renderKnife(Game *game);
void renderCrowbar(Game *game);
void renderPistol(Game *game);
void renderRifle(Game *game);
void renderShield(Game *game);
void renderShotgun(Game *game);
#endif
