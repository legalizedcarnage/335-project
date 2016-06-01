//Author: Miguel Trigueros
//Purpose: I will be creating the enemies and 
//         allowing them to move and hunt the player.
//Progress: Enemies are now tile dependent, they have health
//          and can die. Textures are done and guns to be added.
//Update May 30: Enemies have collision and textures working, not sure
//               guns will be added due to difficulty of game already.

#include <iostream>
#include "main.h"
#include <cstdlib>
#include <cmath>
#include <GL/glx.h>
#include "miguelT.h"

using namespace std;
// Using these counts to keep track of an enemies moves
// This is so it doesnt get stuck doing the same thing.
int xcount[100][100][1];
int ycount[100][100][1];
int ecount[100][100];
int usedx[100];
int usedxcount=0;
int directionx;
int directiony;
float VEL=1.5;
int ecounter=1;
int hardmode=0;
void initEnemies(Game *game, int x, int y) 
{
    game->current_enemies = ecount[x+1][y+1];
    // Enemies are dynamic, start at 2 and goes up by 1 every 2 levels.
    /*if (x % 2 == 0 && x != 0) {
      if (usedxcount == 0) {
      game->num_enemies += ecounter;
      ecount[x+1][y+1] = game->num_enemies;
      game->current_enemies = ecount[x+1][y+1];
      usedx[usedxcount] = x;
      usedxcount++;
      } else {
      bool within = false;
      for (int i = 0; i < usedxcount; i++) {
      if (usedx[i] == x) {
      within = true;
      }
      }
      if (!within) {
      ecounter++;  
      game->num_enemies += ecounter;
      ecount[x+1][y+1] = game->num_enemies;
      game->current_enemies = ecount[x+1][y+1];
      usedx[usedxcount] = x;
      usedxcount++;
      }
      }
      } else {
      ecount[x+1][y+1] = game->num_enemies;
      game->current_enemies = ecount[x+1][y+1];
      }

    //if we have already passed this x and our enemy count went up
    //then we need to make sure that if we return to that x position
    //that we use the saved amount of enemies
    for (int e = 0; e < usedxcount; e++) {
    if (usedx[e] == x) {
    for (int i = 0; i < game->current_; i++) {    
    game->enemies[x+1][y+1][i].s.width = 20;
    game->enemies[x+1][y+1][i].s.height = 30;
    game->enemies[x+1][y+1][i].health = 5;
    int temp = rand() % 100;
    if (temp <= 50) {
    game->enemies[x+1][y+1][i].velocity.y = 0;
    game->enemies[x+1][y+1][i].velocity.x = VEL;
    }
    if (temp > 50) {
    game->enemies[x+1][y+1][i].velocity.y = VEL;
    game->enemies[x+1][y+1][i].velocity.x = 0;
    }
    game->enemies[x+1][y+1][i].s.center.x = 320 + 5*65;
    game->enemies[x+1][y+1][i].s.center.y = 500 - 5*60;
    ycount[x+1][y+1][0] = 0;
    xcount[x+1][y+1][0] = 0;
    game->enemies[x+1][y+1][i].enemiesInit = true;
    game->num_enemies = game->current_enemies;
    return;
    }
    }
    }
     */
    // Check for feature flag on or off
    for (int i = 0; i < game->current_enemies; i++) {    
        game->enemies[x+1][y+1][i].s.width = 20;
        game->enemies[x+1][y+1][i].s.height = 30;
        if (hardmode) {
            game->enemies[x+1][y+1][i].health = 20;
        } else {
            game->enemies[x+1][y+1][i].health = 10;
        }
        int temp = rand() % 100;
        if (temp <= 50) {
            game->enemies[x+1][y+1][i].velocity.y = 0;
            game->enemies[x+1][y+1][i].velocity.x = VEL;
        }
        if (temp > 50) {
            game->enemies[x+1][y+1][i].velocity.y = VEL;
            game->enemies[x+1][y+1][i].velocity.x = 0;
        }
        game->enemies[x+1][y+1][i].s.center.x = 420 + 5*65;
        game->enemies[x+1][y+1][i].s.center.y = 600 - 5*60;
        ycount[x+1][y+1][0] = 0;
        xcount[x+1][y+1][0] = 0;
        game->enemies[x+1][y+1][i].enemiesInit = true;
        game->num_enemies = game->current_enemies;
    }
}

void enemiesMovement(Game *game, int x, int y, int i) 
{
    Player *p;
    p = &game->enemies[x+1][y+1][i];
    if (xcount[x+1][y+1][0] == 0)
        directionx = p->velocity.x;
    if (ycount[x+1][y+1][0] == 0)
        directiony = p->velocity.y;
    objectCollision(game, &game->enemies[x+1][y+1][i]);    
    //Checks for collision with walls
    if (p->s.center.y - p->s.height <= 20 && p->velocity.y < 0) {
        p->s.center.y = p->s.height + 20;
        p->velocity.y *= -1;
        ycount[x+1][y+1][0] += 1;
        if (ycount[x+1][y+1][0] >= 2) {
            int randx = rand() % 10;
            //cout << "randx: " << randx << endl;
            p->velocity.x = 0;
            p->velocity.y *= -1.0;
            if (randx <= 5)
                p->velocity.x = VEL;
            if (randx > 5)
                p->velocity.x = -(VEL);
            ycount[x+1][y+1][0] = 0;
        }
    }
    if (p->s.center.y + p->s.height >= WINDOW_HEIGHT-20 && p->velocity.y > 0) {
        p->s.center.y = WINDOW_HEIGHT - p->s.height - 20;
        p->velocity.y *= -1;
        ycount[x+1][y+1][0] += 1;
        if (ycount[x+1][y+1][0] >= 2) {
            int randx = rand() % 10;
            //cout << "randx: " << randx << endl;
            p->velocity.x = 0;
            p->velocity.y *= 1.0;
            if (randx <= 5)
                p->velocity.x = VEL;
            if (randx > 5)
                p->velocity.x = -(VEL);
            ycount[x+1][y+1][0] = 0;
        }
    }
    if (p->s.center.x - p->s.width <= 20 && p->velocity.x < 0) {
        p->s.center.x = p->s.width + 20;
        p->velocity.x *= -1;
        xcount[x+1][y+1][0] += 1;
        if (xcount[x+1][y+1][0] >= 2) {
            int randy = rand() % 10;
            //cout << "randy: " << randy << endl;
            p->velocity.x *= 1.0;
            p->velocity.y = 0;
            if (randy <= 5)
                p->velocity.y = VEL;
            if (randy > 5)
                p->velocity.y = -(VEL);
            xcount[x+1][y+1][0] = 0;
        }
    }
    if (p->s.center.x + p->s.width >= WINDOW_WIDTH-20 && p->velocity.x > 0) {
        p->s.center.x = WINDOW_WIDTH - 20;
        p->velocity.x *= -1;
        xcount[x+1][y+1][0] += 1;
        if (xcount[x+1][y+1][0] >= 2) {
            int randy = rand() % 10;
            //cout << "randy: " << randy << endl;
            p->velocity.x *= 1.0;
            p->velocity.y = 0;
            if (randy <= 5)
                p->velocity.y = VEL;
            if (randy > 5)
                p->velocity.y = -(VEL);
            xcount[x+1][y+1][0] = 0;
        }
    }
    p->s.center.x += p->velocity.x;
    p->s.center.y += p->velocity.y;
    //cout << "x: " << p->velocity.x << endl;
    //cout << "y: " << p->velocity.y << endl;
}


void playerFound(Game *game, int x, int y, int i)
{
    Player *e;
    e = &game->enemies[x+1][y+1][i];
    Player *p;
    p = &game->player;
    //Checks distance between current enemy and player 
    if (hardmode) {
        if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                    (pow(e->s.center.y - p->s.center.y, 2))) <= 250) {
            if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                        (pow(e->s.center.y - p->s.center.y, 2))) >= 50) { 
                if (p->s.center.x < e->s.center.x && e->velocity.x == 0) {
                    e->velocity.x *= -VEL;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }	    
                if (p->s.center.x > e->s.center.x && e->velocity.x == 0) {
                    e->velocity.x *= VEL;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.x < e->s.center.x && e->velocity.x > 0) {
                    e->velocity.x *= -1.0;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.x > e->s.center.x && e->velocity.x < 0) {
                    e->velocity.x *= -1.0;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.y > e->s.center.y && e->velocity.y < 0) {
                    e->velocity.y *= -1.0;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.y < e->s.center.y && e->velocity.y > 0) {
                    e->velocity.y *= -1.0;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.y > e->s.center.y && e->velocity.y == 0) {
                    e->velocity.y *= VEL;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.y < e->s.center.y && e->velocity.y == 0) {
                    e->velocity.y *= -VEL;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
            }
            //if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
            //            (pow(e->s.center.y - p->s.center.y, 2))) < 50) {
            //    e->velocity.x *= -1.0;
            //    e->velocity.y *= -1.0;
            //    objectCollision(game, &game->enemies[x+1][y+1][i]);    
            //}
        }
    } else {
        if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                    (pow(e->s.center.y - p->s.center.y, 2))) <= 175) {
            if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                        (pow(e->s.center.y - p->s.center.y, 2))) >= 50) { 
                if (p->s.center.x < e->s.center.x && e->velocity.x == 0) {
                    e->velocity.x *= -VEL;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }	    
                if (p->s.center.x > e->s.center.x && e->velocity.x == 0) {
                    e->velocity.x *= VEL;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.x < e->s.center.x && e->velocity.x > 0) {
                    e->velocity.x *= -1.0;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.x > e->s.center.x && e->velocity.x < 0) {
                    e->velocity.x *= -1.0;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.y > e->s.center.y && e->velocity.y < 0) {
                    e->velocity.y *= -1.0;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.y < e->s.center.y && e->velocity.y > 0) {
                    e->velocity.y *= -1.0;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.y > e->s.center.y && e->velocity.y == 0) {
                    e->velocity.y *= VEL;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
                if (p->s.center.y < e->s.center.y && e->velocity.y == 0) {
                    e->velocity.y *= -VEL;
                    objectCollision(game, &game->enemies[x+1][y+1][i]);    
                }
            }
            if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                        (pow(e->s.center.y - p->s.center.y, 2))) < 50) {
                e->velocity.x *= -1.0;
                e->velocity.y *= -1.0;
                objectCollision(game, &game->enemies[x+1][y+1][i]);    
            }
        }
    }
    e->s.center.x += e->velocity.x;
    e->s.center.y += e->velocity.y;
}

void renderEnemies(Game *game, int x, int y)
{
    //resetEnemies(game);
    game->current_enemies = ecount[x+1][y+1];
    for (int i = 0; i < game->current_enemies; i++) {
       // resetEnemies(game);
        enemiesMovement(game, x, y, i);
        objectCollision(game, &game->enemies[x+1][y+1][i]);    
        playerFound(game, x, y,  i);
        removeEnemies(game, x, y, i);
        glColor4f(1.0f,1.0f,1.0f,0.8f);
        float h, w;
        Shape *s;
        //glColor3ub(250,50,50);
        s = &game->enemies[x+1][y+1][i].s;
        Player *e;
        e = &game->enemies[x+1][y+1][i];
        w = s->width;
        h = s->height;
        /*glPushMatrix();
          glTranslatef(s->center.x, s->center.y, s->center.z);
          glBegin(GL_QUADS);
          glVertex2i(-w,-h);
          glVertex2i(-w, h);
          glVertex2i( w, h);
          glVertex2i( w,-h);
          glEnd();
          glPopMatrix();*/
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER,0.0f);
        if (hardmode) {
            glBindTexture(GL_TEXTURE_2D, enemyTexture2);
        } else {
            glBindTexture(GL_TEXTURE_2D, enemyTexture);
        }
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        if (e->velocity.y < 0)
            glVertex2i(s->center.x-w,s->center.y-h);
        else if (e->velocity.y > 0)
            glVertex2i(s->center.x+w,s->center.y+h);
        else if (e->velocity.x < 0)
            glVertex2i(s->center.x-w,s->center.y+h);
        else
            glVertex2i(s->center.x+w,s->center.y-h);
        glTexCoord2f(0.0f, 0.0f);
        if (e->velocity.y < 0)
            glVertex2i(s->center.x-w,s->center.y+h);
        else if (e->velocity.y > 0)
            glVertex2i(s->center.x+w,s->center.y-h);
        else if (e->velocity.x < 0)
            glVertex2i(s->center.x+w,s->center.y+h);
        else
            glVertex2i(s->center.x-w,s->center.y-h);
        glTexCoord2f(1.0f, 0.0f);
        if (e->velocity.y < 0)
            glVertex2i(s->center.x+w,s->center.y+h);
        else if (e->velocity.y > 0)
            glVertex2i(s->center.x-w,s->center.y-h);
        else if (e->velocity.x < 0)
            glVertex2i(s->center.x+w,s->center.y-h);
        else
            glVertex2i(s->center.x-w,s->center.y+h);
        glTexCoord2f(1.0f, 1.0f);
        if (e->velocity.y < 0)
            glVertex2i(s->center.x+w,s->center.y-h);
        else if (e->velocity.y > 0)
            glVertex2i(s->center.x-w,s->center.y+h);
        else if (e->velocity.x < 0)
            glVertex2i(s->center.x-w,s->center.y-h);
        else
            glVertex2i(s->center.x+w,s->center.y+h);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);


    }
}

void removeEnemies(Game *game, int x, int y, int i)
{
    if (game->enemies[x+1][y+1][i].health < 1) {
        int lcount = ecount[x+1][y+1];
        game->enemies[x+1][y+1][i] = game->enemies[x+1][y+1][lcount-1];
        cout << ecount[x+1][y+1] << endl;
        game->current_enemies = --ecount[x+1][y+1];
        cout << ecount[x+1][y+1] << endl;
    }
}

void initEcount(Game *game)
{
    for (int i = 0; i < 100-1; i++) {
        for (int j = 0; j < 100-1; j++) {
            if (i < 2)
                ecount[i+1][j] = 2;
            if (i >= 2 && i < 4) {
                ecount[i+1][j] = 3;
            }
            if (i >= 4 && i < 6) {
                ecount[i+1][j] = 4;
            }
            if (i >=6) {
                ecount[i+1][j] = 5;
            }
        }
    }
}

void objectCollision(Game *game, Player *p)
{
    int y = game->map[1];
    int x = game->map[0];
    if (xcount[x+1][y+1][0] == 0)
        directionx = p->velocity.x;
    if (ycount[x+1][y+1][0] == 0)
        directiony = p->velocity.y;       
    float enemyt = p->s.center.y + p->s.height;
    float enemyb = p->s.center.y - p->s.height;
    float enemyl = p->s.center.x - p->s.width;
    float enemyr = p->s.center.x + p->s.width;
    //cout << game->num_objects << endl;
    Shape *o;
    for (int i = 1; i < game->num_objects; i++) {
        o = &game->object[i];
        if (enemyt >= o->center.y - o->height
                && enemyt <= o->center.y + o->height
                && enemyl < o->center.x + o->width
                && enemyr > o->center.x - o->width
                && p->velocity.y >= 0 ) {
            p->velocity.y *= -1.0;
            ycount[x+1][y+1][0] += 1;
            if (ycount[x+1][y+1][0] >= 2) {
                int randx = rand() % 10;
                //cout << "randy: " << randy << endl;
                if (randx <= 5)
                    p->velocity.x = VEL;
                if (randx > 5)
                    p->velocity.x = -(VEL);
                ycount[x+1][y+1][0] = 0;
            }

        }
        if (enemyb >= o->center.y - o->height
                && enemyb <= o->center.y + o->height
                && enemyl < o->center.x + o->width
                && enemyr > o->center.x - o->width
                && p->velocity.y <= 0 ) {
            p->velocity.y *= -1.0;
            ycount[x+1][y+1][0] += 1;
            if (ycount[x+1][y+1][0] >= 2) {
                int randx = rand() % 10;
                //cout << "randy: " << randy << endl;
                if (randx <= 5)
                    p->velocity.x = VEL;
                if (randx > 5)
                    p->velocity.x = -(VEL);
                ycount[x+1][y+1][0] = 0;
            }
        }
        if (enemyl >= o->center.x - o->width
                && enemyl <= o->center.x + o->width
                && enemyb < o->center.y + o->height
                && enemyt > o->center.y - o->height
                && p->velocity.x <= 0 ) {
            p->velocity.x *= -1.0;
            xcount[x+1][y+1][0] += 1;
            if (xcount[x+1][y+1][0] >= 2) {
                int randy = rand() % 10;
                //cout << "randy: " << randy << endl;
                if (randy <= 5)
                    p->velocity.y = VEL;
                if (randy > 5)
                    p->velocity.y = -(VEL);
                xcount[x+1][y+1][0] = 0;
            }
        }
        if (enemyr >= o->center.x - o->width
                && enemyr <= o->center.x + o->width
                && enemyb < o->center.y + o->height
                && enemyt > o->center.y - o->height
                && p->velocity.x >= 0 ) {
            p->velocity.x *= -1.0;
            xcount[x+1][y+1][0] += 1;
            if (xcount[x+1][y+1][0] >= 2) {
                int randx = rand() % 10;
                //cout << "randy: " << randy << endl;
                if (randx <= 5)
                    p->velocity.x = VEL;
                if (randx > 5)
                    p->velocity.x = -(VEL);
                xcount[x+1][y+1][0] = 0;
            }
        }
    }
}

void resetEnemies(Game *game)
{
        initEcount(game);
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                for (int k = 0; k < 10; k++) {
                    game->enemies[i][j][k].enemiesInit = false;
                }
            }
        }
}

//special feature
void hard ()
{
    hardmode ^= 1;
    if (hardmode) {
        VEL = 2.0;
    } else {
        VEL = 1.5;
    }
}
