//Author: Miguel Trigueros
//Purpose: I will be creating the enemies and 
//         allowing them to move and hunt the player.
//Progress: Enemies are now tile dependent, now to work on enemy
//          Collision with themselves and objects. Weapons afterwards.
//Update May 18: Fixed the bug where the enemy would not initialize
//               at map position 0,-1. Have made the Enemies not stick
//               to walls.

#include <iostream>
#include "main.h"
#include <cstdlib>
#include <cmath>
#include <GL/glx.h>

using namespace std;
// Using these counts to keep track of an emenies moves
// This is so it doesnt get stuck doing the same thing.
int xcount[100][100][1];
int ycount[100][100][1];
int directionx;
int directiony;
float VEL=2.0;

void initEnemies(Game *game, int x, int y, int count) 
{
    //Currently initializing 5 enemies for testing
    //will become dynamic when I apply difficulty per level
    for(int i = 0; i < count; i++) {
        game->enemies[x+1][y+1][i].s.width = 20;
        game->enemies[x+1][y+1][i].s.height = 30;
        int temp = rand() % 100;
        if (temp <= 50) {
            game->enemies[x+1][y+1][i].velocity.y = 0;
            game->enemies[x+1][y+1][i].velocity.x = VEL;
        }
        if (temp > 50) {
            game->enemies[x+1][y+1][i].velocity.y = VEL;
            game->enemies[x+1][y+1][i].velocity.x = 0;
        }
        game->enemies[x+1][y+1][i].s.center.x = 120 + 5*65;
        game->enemies[x+1][y+1][i].s.center.y = 500 - 5*60;
        ycount[x+1][y+1][0] = 0;
        xcount[x+1][y+1][0] = 0;
        game->enemies[x+1][y+1][i].enemiesInit = true;
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
    //still need collision with objects
    if (p->s.center.y - p->s.height <= 20 && p->velocity.y < 0) {
        p->s.center.y = p->s.height + 20;
        p->velocity.y *= -1;
        ycount[x+1][y+1][0] += 1;
        if (ycount[x+1][y+1][0] >= 2) {
            int randx = rand() % 10;
            cout << "randx: " << randx << endl;
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
            cout << "randx: " << randx << endl;
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
            cout << "randy: " << randy << endl;
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
            cout << "randy: " << randy << endl;
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
    cout << "x: " << p->velocity.x << endl;
    cout << "y: " << p->velocity.y << endl;
}


void playerFound(Game *game, int x, int y, int i)
{
    Player *e;
    e = &game->enemies[x+1][y+1][i];
    Player *p;
    p = &game->player;
    //Checks distance between current enemy and player
    //still need to improve how the enemy acts when its within threshold
    if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                (pow(e->s.center.y - p->s.center.y, 2))) <= 150) {
        if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + 
                    (pow(e->s.center.y - p->s.center.y, 2))) >= 50) {
            //cout << "Player Found!" << endl;
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
            //e->velocity.x = p->velocity.x;
            //e->velocity.y = p->velocity.y;
        }
    }
    e->s.center.x += e->velocity.x;
    e->s.center.y += e->velocity.y;
    cout << "x: " << e->velocity.x << endl;
    cout << "y: " << e->velocity.y << endl;
}

void renderEnemies(Game *game, int x, int y, int count)
{
    for (int i = 0; i < count; i++) {
        enemiesMovement(game, x, y, i);
        playerFound(game, x, y,  i);
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


