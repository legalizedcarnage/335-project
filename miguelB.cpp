// Miguel Barrales
// 335
// Prison Escape
// 4/24/16
// Weapon Design : Creates a weapon for the player to shoot enemies
// and movement for the weapon to traverse with the player
// May:8 Shorten function with Julia function and adding them to key to call the function to render each weapon.

// 91 = knife<>
// 92 = crowbar<>
// 93 = shield<>
// 94 = pistol`
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
void mele(Game *game)
{
    static int count = 0;
    if(game->space == 's'){
	for(int i =91; i<94; i++){
		if(game->direction == 'l'){
			game->object[i].center.x = game->object[i].center.x - 1;
		}if(game->direction == 'r'){
			game->object[i].center.x = game->object[i].center.x + 2;
		}if(game->direction == 'u'){
			game->object[i].center.y = game->object[i].center.y + 2;
		}if(game->direction == 'd'){
			game->object[i].center.y = game->object[i].center.y - 1;
		}
	}
	count ++;
	if(count == 100){
		game->mele = false;
		game->space = 0;
		count = 0;
    	}
    }
}

void weaponMov(Game *game)
{
	Player *p;
	p = &game->player;
	for(int i = 91; i <98; i ++) {
		if(game->direction == 'l'){
			game->object[i].center.x = p->s.center.x - 20;
			game->object[i].center.y = p->s.center.y;
		if(game->space == 's'){
			game->mele = true;
			if(game->mele == true){
			mele(game);
			}	
		}	
		}if(game->direction == 'r'){
			game->object[i].center.x = p->s.center.x + 20;
			game->object[i].center.y = p->s.center.y;
		if(game->space == 's'){
			game->mele = true;
		if(game->mele == true){
                	mele(game);
                }
        }
			
		}if(game->direction == 'u'){
			game->object[i].center.x = p->s.center.x;
			game->object[i].center.y = p->s.center.y + 25;
		if(game->space == 's'){
			game->mele = true;
        	if(game->mele == true){
                	mele(game);
                	}
		}
		}if(game->direction == 'd'){
			game->object[i].center.x = p->s.center.x;
			game->object[i].center.y = p->s.center.y - 25;
		if(game->space == 's'){
			game->mele = true;
		if(game->mele == true){
			mele(game);
                		}
        		}
        	}
	
		}if(game->direction == 'l' || game->direction == 'r'){
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
void makeParticle(Game *game, int x, int y)
{
    if (game->n > Max_Particles)
        return;
    std::cout << "makeParticle() " << x << " " << y << std::endl;
    //position of particle
    Particle *p = &game->particle[game->n];
    if (game->gun == '4') {
    p->s.center.x = game->object[94].center.x;
    p->s.center.y = game->object[94].center.y;
    } if(game->gun == '5') {
    p->s.center.x = game->object[95].center.x;
    p->s.center.y = game->object[95].center.y;
    p->t.center.x = game->object[95].center.x;
    p->t.center.y = game->object[95].center.y;
    p->r.center.x = game->object[95].center.x;
    p->r.center.y = game->object[95].center.y;
    } if(game->gun == '6') {
    p->s.center.x = game->object[96].center.x;
    p->s.center.y = game->object[96].center.y;
    } if(game->gun == '7') {
    p->s.center.x = game->object[97].center.x;
    p->s.center.y = game->object[97].center.y;
    }
    //double z = sqrt(x*x + y*y);  

    p->velocity.y = y;
    p->velocity.x = x;
    p->velocity2.y = y - 1;
    p->velocity2.x = x - 1;
    p->velocity3.y = y + 2;
    p->velocity3.x = x + 1;
    game->n++;

}
void renderParticles(Game *game)
{
    	int w = 2;
	int h = 2;
    //draw all particles here
    	for (int i = 0; i < game->n; i++) {
	    glPushMatrix();
		glColor3ub(150,160,220);
		Vec *c = &game->particle[i].s.center;
                int w = 2;
                int h = 2;
		glBegin(GL_QUADS);
		glVertex2i(c->x-w, c->y-h);
		glVertex2i(c->x-w, c->y+h);
		glVertex2i(c->x+w, c->y+h);
		glVertex2i(c->x+w, c->y-h);
		glEnd();
		glPopMatrix();
        }
	for (int i = 0; i < game->n; i++) {
	     glPushMatrix();
		glColor3ub(150,160,220);
		Vec *a = &game->particle[i].t.center;
		w = 2;
	       	h = 2;
                glBegin(GL_QUADS);
                glVertex2i(a->x-w, a->y-h);
                glVertex2i(a->x-w, a->y+h);
                glVertex2i(a->x+w, a->y+h);
                glVertex2i(a->x+w, a->y-h);
                glEnd();
                glPopMatrix();
        }
	for (int i = 0; i < game->n; i++) {
	    	glPushMatrix();
		glColor3ub(150,0,120);
		Vec *b = &game->particle[i].r.center;
		w = 2;
		h = 2;
		glBegin(GL_QUADS);
		glVertex2i(b->x-w, b->y-h);
		glVertex2i(b->x-w, b->y+h);
		glVertex2i(b->x+w, b->y+h);
		glVertex2i(b->x+w, b->y-h);
		glEnd();
		glPopMatrix();
        }
}
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

