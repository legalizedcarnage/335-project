#ifndef MIGUEL_T
#define MIGUEL_T
void initEnemies(Game *game, int x, int y);
void enemiesMovement(Game *game, int x, int y, int i);
void renderEnemies(Game *game, int x, int y);
void playerFound(Game *game, int x, int y, int i);
void removeEnemies(Game *game, int x, int y, int i);
#endif
