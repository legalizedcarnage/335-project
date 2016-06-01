// Miguel Barrales
// 335
// Prison Escape
// 4/24/16
// Weapon Design : Creates a weapon for the player to shoot enemies
// and movement for the weapon to traverse with the player
// May:8 Shorten function with Julia function and adding them to key to call the function to render each weapon.

// 91 = knife<>texture
// 92 = crowbar<>
// 93 = shield<>
// 94 = pistol<>texture
// 95 = shotgun<>texture
// 96 = rifle<>texture
// 97 = stun gun<>

#include <iostream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "main.h"
#include "juliaA.h"
using namespace std;

void weapon(Game *game)
{
	for (int i = 0; i < 7; i++) {
		game->guninv[i] = false;
	}
	game->gun_num = -1;
	declareobject(game, 91, 15, 15, 465, 205);
	declareobject(game, 92, 10, 25, 465, 205);
	declareobject(game, 93, 10, 45, 465, 205);
	declareobject(game, 94, 15, 15, 465, 205);
	declareobject(game, 95, 30, 5, 465, 205);
	declareobject(game, 96, 35, 15, 465, 205);
	declareobject(game, 97, 15, 15, 465, 205);
}
/*void inv(Game *game)
{
	        if (game->gun_num >= 0) {
                if (game->player.s.center.x + game->player.s.width
                > game->object[game->gun_num].center.x
                && game->player.s.center.x - game->player.s.width
                < game->object[game->gun_num].center.x
                && game->player.s.center.y + game->player.s.height
                > game->keys[game->key_num].center.y
                && game->player.s.center.y - game->player.s.height
                < game->keys[game->key_num].center.y) {
                        game->inv[game->gun_num] = true;
                        cout << game->gun_num+1 << endl;
                }
        }
}*/	
void mele(Game *game)
{
    static int count = 0;
    if (game->space == 's') {
	for (int i =91; i<94; i++) {
		if (game->direction == 'l') {
			game->object[i].center.x = game->object[i].center.x - 1;
		} if (game->direction == 'r') {
			game->object[i].center.x = game->object[i].center.x + 2;
		} if (game->direction == 'u') {
			game->object[i].center.y = game->object[i].center.y + 2;
		} if (game->direction == 'd') {
			game->object[i].center.y = game->object[i].center.y - 1;
		}
	}
	count ++;
	if (count == 100) {
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
	for (int i = 91; i <95; i ++) {
		if (game->direction == 'l') {
			game->object[i].center.x = p->s.center.x - 25;
			game->object[i].center.y = p->s.center.y;
		if (game->space == 's') {
			game->mele = true;
			if (game->mele == true) {
			mele(game);
			}	
		}	
		} if (game->direction == 'r') {
			game->object[i].center.x = p->s.center.x + 25;
			game->object[i].center.y = p->s.center.y;
		if (game->space == 's') {
			game->mele = true;
		if (game->mele == true) {
			mele(game);
                } 
        }
			
		} if (game->direction == 'u') {
			game->object[i].center.x = p->s.center.x;
			game->object[i].center.y = p->s.center.y + 30;
		if (game->space == 's') {
			game->mele = true;
		if (game->mele == true) {
			mele(game);
			}
		}
		} if (game->direction == 'd') {
			game->object[i].center.x = p->s.center.x;
			game->object[i].center.y = p->s.center.y - 30;
		if (game->space == 's') {
			game->mele = true;
		if (game->mele == true) {
			mele(game);
				}
			}	
		}
	
		} for (int i = 95; i<98; i++) {
			if (game->direction == 'l') {
			game->object[i].center.x = p->s.center.x - 45;
			game->object[i].center.y = p->s.center.y;
			} if (game->direction == 'r') {
			game->object[i].center.x = p->s.center.x + 45;
			game->object[i].center.y = p->s.center.y;
			} if (game->direction == 'u') {
			game->object[i].center.x = p->s.center.x;
                        game->object[i].center.y = p->s.center.y + 50;
			} if (game->direction == 'd') {
			game->object[i].center.x = p->s.center.x;
			game->object[i].center.y = p->s.center.y - 50;
				}
			}
		if (game->direction == 'l') {
 		game->object[97].center.x = p->s.center.x - 25;
		game->object[97].center.y = p->s.center.y;
		} if (game->direction == 'r') {
		game->object[97].center.x = p->s.center.x + 25;
		game->object[97].center.y = p->s.center.y;
		} if (game->direction == 'u') {
		game->object[97].center.x = p->s.center.x;
		game->object[97].center.y = p->s.center.y + 30;
		if (game->direction == 'd') {
		game->object[97].center.x = p->s.center.x;
		game->object[97].center.y = p->s.center.y - 30;
		}
			
		} if (game->direction == 'l' || game->direction == 'r') {
			game->object[93].width = 10;
			game->object[93].height = 45;
		for (int i = 95; i<97; i ++) {
			game->object[i].width = 30;
			game->object[i].height = 15;
		}
	}
		if (game->direction == 'u' || game->direction == 'd') {
			game->object[93].width = 35;
			game->object[93].height = 10;
		for (int i = 95; i<97; i ++) {
			game->object[i].width = 15;
			game->object[i].height = 30;
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
    game->shot = true;
    p->s.center.x = game->object[94].center.x;
    p->s.center.y = game->object[94].center.y;
    game->n=1;
    } if (game->gun == '5') {
    game->shot = true;
    if (game->n ==0) {
    p->s.center.x = game->object[95].center.x;
    p->s.center.y = game->object[95].center.y;
    game->particle[game->n+1].s.center.x = game->object[95].center.x;
    game->particle[game->n+1].s.center.y = game->object[95].center.y;
    game->particle[game->n+1].velocity.y = y+1;
    game->particle[game->n+1].velocity.x = x+1;
    game->particle[game->n+2].s.center.x = game->object[95].center.x;
    game->particle[game->n+2].s.center.y = game->object[95].center.y;
    game->particle[game->n+2].velocity.y = y-1;
    game->particle[game->n+2].velocity.x = x-1;
    game->n =3;
    }
    } if (game->gun == '6') {
    game->shot = false;
    p->s.center.x = game->object[96].center.x;
    p->s.center.y = game->object[96].center.y;
    } if (game->gun == '7') {
    game->shot = true;
    p->s.center.x = game->object[97].center.x;
    p->s.center.y = game->object[97].center.y;
    game->n=1;
    }

    p->velocity.y = y;
    p->velocity.x = x;
    if (game->shot == false) {
    game->n++;
    }

}
void movement(Game *game)
{
	Particle *p;

	if (game->n <= 0)
	return;
	for (int i = 0; i < game->n; i++) {
	p = &game->particle[i];
	p->s.center.x += p->velocity.x;
	p->s.center.y += p->velocity.y;
	}
}
void renderParticles(Game *game)
{
	int w;
	int h; 
	for (int i = 0; i < game->n; i++) {
		Vec *c = &game->particle[i].s.center;
		if (game->bkey) {
		glPushMatrix();
		glColor3ub(127,127,127);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glBindTexture(GL_TEXTURE_2D, kappaTexture);
                w = 20;
                h = 20;
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(c->x-w, c->y-h);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(c->x-w,c->y+ h);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(c->x+ w,c->y+ h);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(c->x+ w,c->y-h);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();
		}
		if (!(game->bkey)) {
		glPushMatrix();
		glColor3ub(150,160,220);
		w = 2;
		h = 2;
		glBegin(GL_QUADS);
		glVertex2i(c->x-w, c->y-h);
		glVertex2i(c->x-w, c->y+h);
		glVertex2i(c->x+w, c->y+h);
		glVertex2i(c->x+w, c->y-h);
		glEnd();
		glPopMatrix();
			}	   		
	}
}
void renderTexture(Game *game, int i)
{
	Shape *s;
	float w,h;
	glColor4f(1.0f,1.0f,1.0f,0.8f);
        s = &game->object[i];
        w = s->width;
        h = s->height;
	glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER,0.0f);
	if (game->gun == '1') {
        glBindTexture(GL_TEXTURE_2D, gun1Texture);
	} if (game->gun == '2') {
	glBindTexture(GL_TEXTURE_2D, gun2Texture);
	} if (game->gun == '3') {
	glBindTexture(GL_TEXTURE_2D, gun3Texture);
	} if (game->gun == '4') {
	glBindTexture(GL_TEXTURE_2D, gun4Texture);
	} if (game->gun == '5') {
	glBindTexture(GL_TEXTURE_2D, gun6Texture);
	} if (game->gun == '6') {
	glBindTexture(GL_TEXTURE_2D, gun5Texture);
	} if (game->gun == '7') {
	glBindTexture(GL_TEXTURE_2D, gun7Texture);
	}
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
                if (game->direction == 'd')
                        glVertex2i(s->center.x-w,s->center.y-h);
                else if (game->direction == 'u')
                        glVertex2i(s->center.x+w,s->center.y+h);
                else if (game->direction == 'l')
                        glVertex2i(s->center.x-w,s->center.y+h);
                else
                        glVertex2i(s->center.x+w,s->center.y-h);
                glTexCoord2f(0.0f, 0.0f);
                if (game->direction == 'd')
                        glVertex2i(s->center.x-w,s->center.y+h);
                else if (game->direction == 'u')
                        glVertex2i(s->center.x+w,s->center.y-h);
                else if (game->direction == 'l')
                        glVertex2i(s->center.x+w,s->center.y+h);
                else
                        glVertex2i(s->center.x-w,s->center.y-h);
                glTexCoord2f(1.0f, 0.0f);
                if (game->direction == 'd')
                        glVertex2i(s->center.x+w,s->center.y+h);
                else if (game->direction == 'u')
                        glVertex2i(s->center.x-w,s->center.y-h);
                else if (game->direction == 'l')
                        glVertex2i(s->center.x+w,s->center.y-h);
                else
                        glVertex2i(s->center.x-w,s->center.y+h);
                glTexCoord2f(1.0f, 1.0f);
                if (game->direction == 'd')
                        glVertex2i(s->center.x+w,s->center.y-h);
                else if (game->direction == 'u')
                        glVertex2i(s->center.x-w,s->center.y+h);
                else if (game->direction == 'l')
                        glVertex2i(s->center.x-w,s->center.y-h);
                else
                        glVertex2i(s->center.x+w,s->center.y+h);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);
}		
void renderWeapon(Game *game)
{
	if (game->gun == '1') {
	renderTexture(game,91);
	} if (game->gun == '2') {
	renderTexture(game,92);
	} if (game->gun == '3') {
	renderTexture(game,93);
	} if (game->gun == '4') {
	renderTexture(game,94);
	} if (game->gun == '5') {
	renderTexture(game,95);
	} if (game->gun == '6') {
	renderTexture(game,96);
	} if (game->gun == '7') {
	renderTexture(game,97);
	}
}

