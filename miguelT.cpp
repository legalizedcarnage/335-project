//Author: Miguel Trigueros
//Purpose: I will be creating the enemies and allowing them to move and hunt the player.
//Progress: Currently have basic movement but I need to make an enemy stay within its own tile.
//	    Was able to add more enemies with their own movement, still need to make them be associated with a tile.
//Update May 2: Added basic detection of player if they are within a threshold, still working on keeping them on their own tile. 
#include <iostream>
#include "main.h"
#include <cstdlib>
#include <cmath>
#include <GL/glx.h>

using namespace std;

int xcount[10][1];
int ycount[10][1];
int directionx;
int directiony;

void initEnemies(Game *game) 
{
    //Currently initializing 5 enemies for testing
    //will become dynamic when I apply difficulty per level
    for (int i = 0; i < 5; i++) {
	game->enemies[i].s.width = 20;
	game->enemies[i].s.height = 30;
	game->enemies[i].velocity.x = 4;
	game->enemies[i].velocity.y = 0;
	game->enemies[i].s.center.x = 120 + 5*65;
	game->enemies[i].s.center.y = 500 - 5*60;
	ycount[i][0] = 0;
	xcount[i][0] = 0;
    }
}

void enemiesMovement(Game *game, int i) 
{
    Player *p;
    p = &game->enemies[i];
    if(xcount[i][0] == 0)
	directionx = p->velocity.x;
    if(ycount[i][0] == 0)
	directiony = p->velocity.y;
    //Checks for collision with walls
    //still need collision with objects
    if (p->s.center.y - p->s.height <= 20 && p->velocity.y < 0) {
	p->s.center.y = p->s.height + 20;
	p->velocity.y *= -1;
	ycount[i][0] += 1;
	if(ycount[i][0] >= 2) {
	    int randx = rand() % 10;
	    cout << "randx: " << randx << endl;
	    p->velocity.x = 0;
	    p->velocity.y = 0;
	    if(randx <= 5)
		p->velocity.x = 4;
	    if(randx > 5)
		p->velocity.x = -4;
	    ycount[i][0] = 0;
	}
    }
    if (p->s.center.y + p->s.height >= WINDOW_HEIGHT-20 && p->velocity.y > 0) {
	p->s.center.y = WINDOW_HEIGHT - p->s.height - 20;
	p->velocity.y *= -1;
	ycount[i][0] += 1;
	if(ycount[i][0] >= 2) {
	    int randx = rand() % 10;
	    cout << "randx: " << randx << endl;
	    p->velocity.x = 0;
	    p->velocity.y = 0;
	    if(randx <= 5)
		p->velocity.x = 4;
	    if(randx > 5)
		p->velocity.x = -4;
	    ycount[i][0] = 0;
	}
    }
    if (p->s.center.x - p->s.width <= 20 && p->velocity.x < 0) {
	p->s.center.x = p->s.width + 20;
	p->velocity.x *= -1;
	xcount[i][0] += 1;
	if(xcount[i][0] >= 2) {
	    int randy = rand() % 10;
	    cout << "randy: " << randy << endl;
	    p->velocity.x = 0;
	    p->velocity.x = 0;
	    if(randy <= 5)
		p->velocity.y = 4;
	    if(randy > 5)
		p->velocity.y = -4;
	    xcount[i][0] = 0;
	}
    }
    if (p->s.center.x + p->s.width >= WINDOW_WIDTH-20 && p->velocity.x > 0) {
	p->s.center.x = WINDOW_WIDTH - 20;
	p->velocity.x *= -1;
	xcount[i][0] += 1;
	if(xcount[i][0] >= 2) {
	    int randy = rand() % 10;
	    cout << "randy: " << randy << endl;
	    if(randy <= 5)
		p->velocity.y = 4;
	    if(randy > 5)
		p->velocity.y = -4;
	    xcount[i][0] = 0;
	}
    }
    p->s.center.x += p->velocity.x;
    p->s.center.y += p->velocity.y;
    cout << "x: " << p->velocity.x << endl;
    cout << "y: " << p->velocity.y << endl;
}


void playerFound(Game *game, int i)
{
    Player *e;
    e = &game->enemies[i];
    Player *p;
    p = &game->player;
    //Checks distance between current enemy and player
    //still need to improve how the enemy acts when its within threshold
    if ( sqrt((pow(e->s.center.x - p->s.center.x, 2)) + (pow(e->s.center.y - p->s.center.y, 2))) <= 150) {
	cout << "Player Found!" << endl;
	if (p->s.center.x < e->s.center.x && e->velocity.x > 0) {
	    e->velocity.x *= -1;
	}
	if (p->s.center.x > e->s.center.x && e->velocity.x < 0) {
	    e->velocity.x *= -1;
	}
	if (p->s.center.y < e->s.center.y && e->velocity.y > 0) {
	    e->velocity.y *= -1;
	}
	if (p->s.center.y > e->s.center.y && e->velocity.y < 0) {
	    e->velocity.y *= -1;
	}
	//e->velocity.x = p->velocity.x;
	//e->velocity.y = p->velocity.y;
    }
    e->s.center.x += e->velocity.x;
    e->s.center.y += e->velocity.y;
    cout << "x: " << e->velocity.x << endl;
    cout << "y: " << e->velocity.y << endl;
}

void renderEnemies(Game *game)
{
    for (int i = 0; i < 5; i++) {
	enemiesMovement(game, i);
	playerFound(game, i);
	float h, w;
	Shape *s;
	glColor3ub(250,50,50);
	s = &game->enemies[i].s;
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


