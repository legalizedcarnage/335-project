#ifndef DAVIS_H
#define DAVIS_H
void shiftScreen(Game *game, char direction);
void playerCollision(Game *game);
void particleCollision(Game *game);
void Player_Object(Game *game, Player *p);
void Respawn(Game *game);
#endif 
