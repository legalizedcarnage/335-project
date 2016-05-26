//Author: Miguel Trigueros
//Purpose: I will be creating the enemies and 
//         allowing them to move and hunt the player.
//Progress: Enemies are now tile dependent, they have health
//          and can die..
//Update May 25: Gave enemies health and they also can die now
//               Addding object collision tonight and weapons later.

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
int ecounter=0;

void initEnemies(Game *game, int x, int y) 
{
    // Enemies are dynamic, start at 2 and goes up by 1 every 2 levels.
    if (x % 2 == 0 && x != 0) {
        if (usedxcount == 0) {
            game->current_enemies += ecounter;
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
                game->current_enemies += ecounter;
                usedx[usedxcount] = x;
                usedxcount++;
            }
        }
    }
    //if we have already passed this x and our enemy count went up
    //then we need to make sure that if we return to that x position
    //that we use the saved amount of enemies
    for (int e = 0; e < usedxcount; e++) {
        if (usedx[e] == x) {
            for(int i = 0; i < usedx[e]; i++) {    
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
                ecount[x+1][y+1] = game->current_enemies;
                return;
            }
        }
    }
    for(int i = 0; i < game->current_enemies; i++) {    
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
        ecount[x+1][y+1] = game->current_enemies;
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
    if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                (pow(e->s.center.y - p->s.center.y, 2))) <= 150) {
        if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                    (pow(e->s.center.y - p->s.center.y, 2))) >= 50) {
            if (p->s.center.x < e->s.center.x && e->velocity.x > 0) {
                e->velocity.x *= -1.0;
            }
            if (p->s.center.x > e->s.center.x && e->velocity.x < 0) {
                e->velocity.x *= -1.0;
            }
            if (p->s.center.y < e->s.center.y && e->velocity.y > 0) {
                e->velocity.y *= -1.0;
            }
            if (p->s.center.y > e->s.center.y && e->velocity.y < 0) {
                e->velocity.y *= -1.0;
            }
        }
        if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                    (pow(e->s.center.y - p->s.center.y, 2))) < 50) {
            e->velocity.x *= -1.0;
            e->velocity.y *= -1.0;
            e->health -= 1;
        }
    }
    e->s.center.x += e->velocity.x;
    e->s.center.y += e->velocity.y;
}

void renderEnemies(Game *game, int x, int y)
{
    for (int i = 0; i < game->current_enemies; i++) {
        enemiesMovement(game, x, y, i);
        playerFound(game, x, y,  i);
        removeEnemies(game, x, y, i);
        float h, w;
        Shape *s;
        glColor3ub(250,50,50);
        s = &game->enemies[x+1][y+1][i].s;
        glPushMatrix();
        glTranslatef(s->center.x, s->center.y, s->center.z);
        w = s->width;
        h = s->height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w, h);
        glVertex2i( w, h);
        glVertex2i( w,-h);
        glEnd();
        glPopMatrix();
    }
}

void removeEnemies(Game *game, int x, int y, int i)
{
    if (game->enemies[x+1][y+1][i].health < 1) {
        int lcount = ecount[x+1][y+1];
        game->enemies[x+1][y+1][i] = game->enemies[x+1][y+1][lcount];
        ecount[x+1][y+1]--;
    }
}
