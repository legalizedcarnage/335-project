#include <iostream>
#include "main.h"
#include <cstdlib>
using namespace std;
int xcount;
int ycount;
int directionx;
int directiony;

void initEnemies(Game *game) 
{
    game->enemies[0].s.width = 20;
    game->enemies[0].s.height = 30;
    game->enemies[0].velocity.x = 8;
    game->enemies[0].velocity.y = 0;
    game->enemies[0].s.center.x = 120 + 5*65;
    game->enemies[0].s.center.y = 500 - 5*60;
    ycount = 0;
    xcount = 0;
}

void enemiesMovement(Game *game) 
{
    Player *p;
    p = &game->enemies[0];
    if(xcount == 0)
	directionx = p->velocity.x;
    if(ycount == 0)
	directiony = p->velocity.y;

    if (p->s.center.y - p->s.height <= 20 && p->velocity.y < 0) {
	p->s.center.y = p->s.height + 20;
	p->velocity.y *= -1;
	ycount++;
	if(ycount >= 2) {
	    int randx = rand() % 10;
	    cout << "randx: " << randx << endl;
	    p->velocity.x = 0;
	    p->velocity.y = 0;
	    if(randx <= 5)
		p->velocity.x = 8;
	    if(randx > 5)
		p->velocity.x = -8;
	    ycount = 0;
	}
    }
    if (p->s.center.y + p->s.height >= WINDOW_HEIGHT-20 && p->velocity.y > 0) {
	p->s.center.y = WINDOW_HEIGHT - p->s.height - 20;
	p->velocity.y *= -1;
	ycount++;
	if(ycount >= 2) {
	    int randx = rand() % 10;
	    cout << "randx: " << randx << endl;
	    p->velocity.x = 0;
	    p->velocity.y = 0;
	    if(randx <= 5)
		p->velocity.x = 8;
	    if(randx > 5)
		p->velocity.x = -8;
	    ycount = 0;
	}
    }
    if (p->s.center.x - p->s.width <= 20 && p->velocity.x < 0) {
	p->s.center.x = p->s.width + 20;
	p->velocity.x *= -1;
	xcount++;
	if(xcount >= 2) {
	    int randy = rand() % 10;
	    cout << "randy: " << randy << endl;
	    p->velocity.x = 0;
	    p->velocity.x = 0;
	    if(randy <= 5)
		p->velocity.y = 8;
	    if(randy > 5)
		p->velocity.y = -8;
	    xcount = 0;
	}
    }
    if (p->s.center.x + p->s.width >= WINDOW_WIDTH-20 && p->velocity.x > 0) {
	p->s.center.x = WINDOW_WIDTH - 20;
	p->velocity.x *= -1;
	xcount++;
	if(xcount >= 2) {
	    int randy = rand() % 10;
	    cout << "randy: " << randy << endl;
	    if(randy <= 5)
		p->velocity.y = 8;
	    if(randy > 5)
		p->velocity.y = -8;
	    xcount = 0;
	}
    }
    p->s.center.x += p->velocity.x;
    p->s.center.y += p->velocity.y;
    cout << "x: " << p->velocity.x << endl;
    cout << "y: " << p->velocity.y << endl;
}
