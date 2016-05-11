// Miguel Barrales
// 335
// Prison Escape
// 4/24/16
// Weapon Design : Creates a weapon for the player to shoot enemies
// and movement for the weapon to traverse with the player
// May:8 Shorten function with Julia function and adding them to key to call the function to render each weapon.

// 90 = knife
// 91 = crowbar
// 92 = shield
// 93 = pistol
// 94 = shotgun
// 95 = rifle
// 96  = stun gun

#include <iostream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "main.h"
#include "juliaA.h"
using namespace std;

//initilaze weapon on top of player to layer
//in main its set to player to follow the player around
void weapon(Game *game)
{
	declareobject(game, 91, 10, 10, 465, 205);
	declareobject(game, 92, 10, 10, 465, 205);
	declareobject(game, 93, 30, 30, 465, 205);
	declareobject(game, 94, 10, 10, 465, 205);
	declareobject(game, 95, 20, 5, 465, 205);
	declareobject(game, 96, 20, 5, 465, 205);
	declareobject(game, 97, 20, 5, 465, 205);
}
//render weapons && in main it layer on top of player
void renderWeapon(Game *game)
{
	if(game->gun == '1'){
	glColor3ub(244,226,13);
	drawobject(game,91);
	}if(game->gun == '2'){
	glColor3ub(244,226,13);
	drawobject(game,92);
	}if(game->gun == '3'){
	glColor3ub(244,226,13);
	drawobject(game,93);
	}if(game->gun == '4'){
	glColor3ub(244,226,13);
	drawobject(game,94);
	}if(game->gun == '5'){
	glColor3ub(244,226,13);
	drawobject(game,95);
	}if(game->gun == '6'){
	glColor3ub(244,226,13);
	drawobject(game,96);
	}if(game->gun == '7'){
	glColor3ub(244,222,39);
	drawobject(game,97);
	}
}

