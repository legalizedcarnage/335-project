// Miguel Barrales
// 335
// Prison Escape
// 4/24/16
// Weapon Design : Creates a weapon for the player to shoot enemies
// and movement for the weapon to traverse with the player
// May:8 Shorten function with Julia function and adding them to key to call the function to render each weapon.

// 91 = knife
// 92 = crowbar
// 93 = shield
// 94 = pistol
// 95 = shotgun
// 96 = rifle
// 97 = stun gun

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
	declareobject(game, 93, 5, 30, 465, 205);
	declareobject(game, 94, 10, 10, 465, 205);
	declareobject(game, 95, 20, 5, 465, 205);
	declareobject(game, 96, 20, 5, 465, 205);
	declareobject(game, 97, 20, 5, 465, 205);
}
void weaponMov(Game *game)
{
        Player *p;
        p = &game->player;
	for(int i = 91; i <98; i ++) {
        if(game->direction == 'l'){
        game->object[i].center.x = p->s.center.x - 20;
        game->object[i].center.y = p->s.center.y;
        }if(game->direction == 'r'){
        game->object[i].center.x = p->s.center.x + 20;
        game->object[i].center.y = p->s.center.y;
        }if(game->direction == 'u'){
        game->object[i].center.x = p->s.center.x;
        game->object[i].center.y = p->s.center.y + 25;
	}if(game->direction == 'd'){
        game->object[i].center.x = p->s.center.x;
        game->object[i].center.y = p->s.center.y - 25;
        	}
	}
	if(game->direction == 'l' || game->direction == 'r'){
	game->object[93].width = 5;
	game->object[93].height = 30;
	for(int i = 95; i<98; i ++){
	game->object[i].width = 20;
        game->object[i].height = 5;
  		}
	}

	if(game->direction == 'u' || game->direction == 'd'){
        game->object[93].width = 30;
        game->object[93].height = 5;
	for(int i = 95; i<98; i ++){
        game->object[i].width = 5;
        game->object[i].height = 20;
                }
	}
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

