// Miguel Barrales
// 335
// Prison Escape
// 4/24/16
// Weapon Design : Creates a weapon for the player to shoot enemies
// and movement for the weapon to traverse with the player

#include <iostream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "main.h"
using namespace std;

//initilaze weapon on top of player to layer
//in main its set to player to follow the player around
void knife(Game *game)
{	
	game->knife.k.width = 10;
        game->knife.k.height = 15;
        game->knife.k.center.x = 465; 
        game->knife.k.center.y = 205;
        game->knife.velocity.x = 0;
        game->knife.velocity.y = 0;

}
//render weapons && in main it layer on top of player
void renderKnife(Game *game)
{
	Shape *k;
	float w,h;
	glColor3ub(255,255,0);
	k = &game->knife.k;
	glPushMatrix();
	glTranslatef(k->center.x, k->center.y, k->center.z);
	w = k->width;
	h = k->height;
	glBegin(GL_QUADS);
	glVertex2i(-w,-h);
	glVertex2i(-w, h);
	glVertex2i( w, h);
	glVertex2i( w,-h);
	glEnd();
	glPopMatrix();	
}

