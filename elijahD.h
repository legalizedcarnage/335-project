#ifndef DAVIS_H
#define DAVIS_H
void shiftScreen(Game *game, char direction);
void playerCollision(Game *game);
void particleCollision(Game *game);
void Player_Object(Game *game, Player *p);
void Respawn(Game *game);
void key(Game *game);
void init_keys(Game *game);
void Print_keys(Game *game);
void player_Wall(Game *game);
void interact(Game *game);
void doors(Game *game);
void text(Game *game);
void gameover(Game *game);
#endif 
