//Elijah Davis
//cs 335
//started 4/22/16
//screen transitions and collision detection of player
//and bullets with each other, the walls, and objects
//started 5/19/16
//interactable objects such as walls and gates that need 
//to be matched with correct keys
#include <iostream>
#include <stdlib.h>
#include <GL/glx.h>
#include <unistd.h>
#include "ppm.h"
#include "main.h"
#include "miguelT.h"
#include "marioH.h"
extern "C" {
#include "fonts.h"
}
//key image
Ppmimage *keyImage = NULL;
GLuint keyTexture;
GLuint alphaKeyTexture;
using namespace std;
void Respawn(Game *game)
{	
	resetEnemies(game);
	game->map[0] = 0;
	game->map[1] = 0;
	game->player.health = Start_HP;	
	initPlayer(game);
}
void gameover(Game *game) 
{
	static int count = 0;
	Rect dead;
	dead.bot = rand()%WINDOW_HEIGHT;
	dead.left = rand()%WINDOW_WIDTH;
	dead.center = 0;
	ggprint16(&dead,10,0x00ffffff,"game over");

	count++;
	if (count == 100) {
		game->state = 1;
		Respawn(game);
		count = 0;
	}	
}
//used when player collides with wall to shift to new tile
void shiftScreen(Game *game, char direction)
{
	if (direction == 'u') {
		game->map[1]++;
	}
	if (direction == 'd') {
		game->map[1]--;
	}
	if (direction == 'l') {
		game->map[0]--;
	}
	if (direction == 'r') {
		game->map[0]++;
	}
	if (!game->enemies[game->map[0]+1][game->map[1]+1][0].enemiesInit)	
		initEnemies(game, game->map[0], game->map[1]);
}
void Player_Object(Game *game, Player *p, Shape *objects,int start, int num)
{
	float top = p->s.center.y  + p->s.height;
	float bot = p->s.center.y  - p->s.height;
	float left = p->s.center.x - p->s.width;
	float right = p->s.center.x + p->s.width;
	
	Shape *s;
	for (int i = start; i < num; i++) {
		s = &objects[i];

		if (top >= s->center.y - s->height
		&& top <= s->center.y + s->height
		&& left < s->center.x + s->width
		&& right > s->center.x - s->width
		&& p->velocity.y > 0 ) {
			if ( top > s->center.y - s->height) 
				p->s.center.y -= top -  (s->center.y -s->height);
			p->velocity.y = 0;
		}
		if (bot >= s->center.y - s->height
		&& bot <= s->center.y + s->height
		&& left < s->center.x + s->width
		&& right > s->center.x - s->width
		&& p->velocity.y < 0 ) {
			if ( bot < s->center.y + s->height) 
				p->s.center.y -= bot -  (s->center.y + s->height);
			p->velocity.y = 0;
		}
		if (left >= s->center.x - s->width
		&& left <= s->center.x + s->width
		&& bot < s->center.y + s->height
		&& top > s->center.y - s->height
		&& p->velocity.x < 0 ) {
			if ( left < s->center.x + s->width) 
				p->s.center.x -= left -  (s->center.x + s->width);
			p->velocity.x = 0;
		} 
		if (right >= s->center.x - s->width
		&& right <= s->center.x + s->width
		&& bot < s->center.y + s->height
		&& top > s->center.y - s->height
		&& p->velocity.x > 0 ) {
			if ( right > s->center.x - s->width) 
				p->s.center.x -= right -  (s->center.x -s->width);
			p->velocity.x = 0;
		}	
	}
}
void player_Wall (Game *game) 
{
	//detect screen collisions
	Player *p;
	p = &game->player;
	//defined edges
	float top = p->s.center.y  + p->s.height;
	float bot = p->s.center.y  - p->s.height;
	float left = p->s.center.x - p->s.width;
	float right = p->s.center.x + p->s.width;
	//floor
	if (bot <= 0 && p->velocity.y < 0) {
		p->s.center.y = WINDOW_HEIGHT - p->s.height;
		shiftScreen(game, 'd');
	}
	//roof
	if (top >= WINDOW_HEIGHT && p->velocity.y > 0) {
		p->s.center.y = p->s.height;
		shiftScreen(game, 'u');
	}
	//left wall
	if (left <= 0 && p->velocity.x < 0) {
		p->s.center.x = WINDOW_WIDTH - p->s.width;
		shiftScreen(game, 'l');
	}
	//right wall
	if (right >= WINDOW_WIDTH && p->velocity.x > 0) {
		p->s.center.x = p->s.width;
		shiftScreen(game, 'r');
	}


}
void playerCollision(Game *game)
{
	Player *p;
	p = &game->player;
	//defined edges
	float top = p->s.center.y  + p->s.height;
	float bot = p->s.center.y  - p->s.height;
	float left = p->s.center.x - p->s.width;
	float right = p->s.center.x + p->s.width;
	
	void key(Game *game);
	key(game);

	//detect object collisions //added enemy collision
	Player_Object(game, &game->player,game->object,0,game->num_objects);
	//player-enemy collision
	for ( int i = 0; i < game->current_enemies; i++) {
		Player *e;
		e = &game->enemies[game->map[0]+1][game->map[1]+1][i];	
		float enemy_b = 
			e->s.center.y - e->s.height;
		float enemy_t = 
			e->s.center.y + e->s.height;
		float enemy_l = 
			e->s.center.x - e->s.width;
		float enemy_r = 
			e->s.center.x + e->s.width;
		if (top+15 >= enemy_b &&
		bot-15 <= enemy_t &&
		left-15 <= enemy_r &&
		right+15 >= enemy_l) {
			if ((game->gun == '1' || game->gun == '2' 
			|| game->gun == '3') && game->mele == true)
				e->health -= .2;
		}
		if (top >= enemy_b &&
		bot <= enemy_t &&
		left <= enemy_r &&
		right >= enemy_l) {
			if ((game->gun == '1' || game->gun == '2' 
			|| game->gun == '3') && game->mele == true)
				e->health -= 5;
			else 
				p->health--;
			//knocked back when hit enemy
			int min_distY = 100;
			int min_distX = 100;
			int base = 15; 
			for (int j = 0; j < game->num_objects; j++) {
				//ceiling
				if (abs(top - (game->object[j].center.y - 
				game->object[j].height))  >= 
				base) {
					if (base
					<= abs(min_distY)) {
						min_distY = 
						base*( p->s.center.y 
						- e->s.center.y)
						/abs(p->s.center.y - e->s.center.y);
						if (p->s.center.y - e->s.center.y 
							== 0) {
							min_distY = 0;
						}
					}
				
				} else {
					min_distY =
					-(top - (game->object[j].center.y - 
					game->object[j].height));
				}
				//floor
				if (abs(bot - (game->object[j].center.y + 
				game->object[j].height)) >=
				base) {
					if (base 
					<= abs(min_distY)) {
						min_distY =
						base*( p->s.center.y 
							- e->s.center.y)
						/abs(p->s.center.y - e->s.center.y);
						if (p->s.center.y - e->s.center.y 
							== 0) {
							min_distY = 0;
						}
					}
				} else {
					min_distY =
					-(bot - (game->object[j].center.y +
					game->object[j].height));
				}
				//sides
				if (abs(right - (game->object[j].center.x - 
				game->object[j].width))  >= 
				base) {
					if (base 
					<= abs(min_distX)) {
						min_distX = 
						base*(p->s.center.x 
						- e->s.center.x)/
						abs(p->s.center.x - e->s.center.x);
						if (p->s.center.x - e->s.center.x
						== 0) {
							min_distX = 0;
						}
					}
				} else {	
					min_distX =
					-(right - (game->object[j].center.x - 
					game->object[j].width));
				}
				if (abs(left - (game->object[j].center.x + 
				game->object[j].width)) >=
				base) {
					if (base  
					<= abs(min_distX)) {
						min_distX =
						base*(p->s.center.x 
						- e->s.center.x)/
						abs(p->s.center.x - e->s.center.x);
						if (p->s.center.x - e->s.center.x 
						== 0) {
							min_distX = 0;
						}
					}
				} else {
					min_distX =
					-(left - (game->object[j].center.x +
					game->object[j].width));
				}
			}
			p->s.center.x += min_distX;
			e->s.center.x -= min_distX;
			e->velocity.x *= -1;
			p->s.center.y += min_distY;
			e->s.center.y -= min_distY;
			e->velocity.y *= -1;	
		}
	}	
	player_Wall(game);
	if (game->player.health <= 0) {
		//Respawn(game);
		game->state = 10;

	}
}
void particleCollision(Game *game) 
{
	Player *play;
	play = &game->player;
	float top = play->s.center.y  + play->s.height;
	float bot = play->s.center.y  - play->s.height;
	float left = play->s.center.x - play->s.width;
	float right = play->s.center.x + play->s.width;
	
	Particle *p;
	Shape *s;
	
	for (int i = 0; i < game->n; i++) {
		p = &game->particle[i];
		//check for bullet collision with player
		if (p->s.center.x > bot
		&& p->s.center.x < top
		&& p->s.center.y >left	
		&& p->s.center.y < right) {
			*p = game->particle[game->n-1];
			game->n--;
			play->health--;
		}
			
		//check for bullet collisions with enemies
		for (int j = 0; j < game->current_enemies; j++) {
			Player *e = &game->enemies[game->map[0]+1][game->map[1]+1][j];	
			float botE = e->s.center.y - e->s.height;
			float topE = e->s.center.y  + e->s.height;
			float leftE = e->s.center.x - e->s.width;
			float rightE = e->s.center.x + e->s.width;

			if (p->s.center.y > botE
			&& p->s.center.y < topE
			&& p->s.center.x >leftE	
			&& p->s.center.x < rightE) {
				*p = game->particle[game->n-1];
				game->n--;
				e->health--;
		
			}
			if (e->health == 0) {
				
			}
		}
		//check for bullet collision with enviornment
		for (int j = 0; j < game->num_objects; j++) {
			s = &game->object[j];
			
			if (p->s.center.x <= s->center.x + s->width
			&& p->s.center.x >= s->center.x - s->width
			&& p->s.center.y <= s->center.y 	+ s->height
			&& p->s.center.y >= s->center.y - s->height) {
				*p = game->particle[game->n-1];
				game->n--;
				break;
			}
		}
		//check for off-screen
		if (p->s.center.x > WINDOW_WIDTH + p->s.width) {
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.x < 0.0) {
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.y > WINDOW_HEIGHT + p->s.height) {
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.y < 0.0) {
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
	
	}
}
// interactables
void init_keys(Game *game)
{
	for (int i = 0; i< 5; i++) {
		game->inv[i] = false;
	}
	game->key_num = -1;
	game->keys[0].center.x = 1000;
	game->keys[0].center.y = 200;
	game->keys[0].width = 10;
	game->keys[0].height = 10;

	game->keys[1].center.x = 1000;
	game->keys[1].center.y = 200;
	game->keys[1].width = 10;
	game->keys[1].height = 10;

	game->keys[2].center.x = 1000;
	game->keys[2].center.y = 200;
	game->keys[2].width = 10;
	game->keys[2].height = 10;

	game->keys[3].center.x = 100;
	game->keys[3].center.y = 800;
	game->keys[3].width = 10;
	game->keys[3].height = 10;

	game->keys[4].center.x = 1000;
	game->keys[4].center.y = 200;
	game->keys[4].width = 10;
	game->keys[4].height = 10;
	
}
void Print_keys(Game *game) 
{
	keyImage = ppm6GetImage("key.ppm");
	glGenTextures(1,&keyTexture);
	glBindTexture(GL_TEXTURE_2D, keyTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		keyImage->width, keyImage->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, keyImage->data);
	glGenTextures(1, &alphaKeyTexture);
	unsigned char *alphaKeyData = buildAlphaData(keyImage);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,keyImage->width,
		keyImage->height,0, GL_RGBA,GL_UNSIGNED_BYTE,alphaKeyData);
	free(alphaKeyData);	
	game->key_num = -1;
	//check if key should be printed on tile
	if (game->map[0] == 0 && game->map[1] ==1) {
		game->key_num = 0;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
		glColor3ub(90,140,90);
	}
	if (game->map[0] == 4 && game->map[1] ==-1) {
		game->key_num = 1;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
		glColor3ub(90,90,140);
	}	
	if (game->map[0] == 5 && game->map[1] ==0) {
		game->key_num = 2;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
		glColor3ub(140,90,90);
	}	
	if (game->map[0] == 3 && game->map[1] ==2) {
		game->key_num = 3;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
		glColor3ub(140,140,90);
	}	
	if (game->map[0] == 5 && game->map[1] ==2) {
		game->key_num = 4;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
		glColor3ub(200,160,150);
	}	
	if (game->key_num >= 0) {
		Shape *s;
		float w, h;
		s = &game->keys[game->key_num];
		w = s->width;
		h = s->height;
		glPushMatrix();
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBindTexture(GL_TEXTURE_2D, keyTexture);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); 
			glVertex2i(s->center.x-w,s->center.y-h);
				glTexCoord2f(0.0f, 0.0f); 
			glVertex2i(s->center.x-w,s->center.y+ h);
				glTexCoord2f(1.0f, 0.0f); 
			glVertex2i(s->center.x+ w,s->center.y+ h);
				glTexCoord2f(1.0f, 1.0f); 
			glVertex2i(s->center.x+ w,s->center.y-h);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();
	}
}
void key(Game *game) 
{
	if (game->key_num >= 0) {
		if (game->player.s.center.x + game->player.s.width  
		> game->keys[game->key_num].center.x
		&& game->player.s.center.x - game->player.s.width 
		< game->keys[game->key_num].center.x
		&& game->player.s.center.y + game->player.s.height 
		> game->keys[game->key_num].center.y
		&& game->player.s.center.y - game->player.s.height 
		< game->keys[game->key_num].center.y) {
			game->inv[game->key_num] = true;
		}
	}
}
void doors(Game *game) 
{
	
	//door1
	game->interact[0].width = 10;
	game->interact[0].height = 350;
	game->interact[0].center.x = WINDOW_WIDTH-10;
	game->interact[0].center.y = 800;
	game->interact[1].width = 10;
	game->interact[1].height = 350;
	game->interact[1].center.x = 10;
	game->interact[1].center.y = 800;
	game->interact[2].width = 20;
	game->interact[2].height = 550;
	game->interact[2].center.x = WINDOW_WIDTH-10;
	game->interact[2].center.y = 800;
	game->interact[3].width = 10;
	game->interact[3].height = 350;
	game->interact[3].center.x = WINDOW_WIDTH-10;
	game->interact[3].center.y = 800;
	game->interact[4].width = 10;
	game->interact[4].height = 350;
	game->interact[4].center.x = WINDOW_WIDTH-10;
	game->interact[4].center.y = 800;


	//print
	Shape *s;
	float w, h;
	if (game->map[0] == 2 && game->map[1] == -1 && game->open[0] == false) {
		s = &game->interact[0];
		Player_Object(game, &game->player, game->interact,0, 1);	
	} else if (game->map[0] == 1 && game->map[1] == -1 
		&& game->open[1] == false) {
		Player_Object(game, &game->player, game->interact, 1,2);	
		s = &game->interact[1];
	} else if (game->map[0] == 5 && game->map[1] == 1 
		&& (game->open[2] == false || game->open[3] == false 
		|| game->open[4] == false)) {
		Player_Object(game, &game->player, game->interact, 2,3);	
		s = &game->interact[2];
	}
	if ((game->map[0] == 2 && game->map[1] == -1 && game->open[0] == false) 
	||  (game->map[0] == 1 && game->map[1] == -1 && game->open[1] == false) 
	||  (game->map[0] == 5 && game->map[1] == 1 && (game->open[2] == false
	||  game->open[3] == false || game->open[4]==false))) {
		glColor3ub(100,100,100);
		glPushMatrix();
		w = s->width;
		h = s->height;
		glBegin(GL_QUADS);
			glVertex2i(s->center.x-w,s->center.y-h);
			glVertex2i(s->center.x-w, s->center.y+h);
			glVertex2i(s->center.x+ w,s->center.y+ h);
			glVertex2i(s->center.x+ w,s->center.y-h);
		glEnd();
		glPopMatrix();
	}
}
void interact(Game *game) 
{
	Shape *p = &game->player.s;
	float top = p->center.y  + p->height;
	float bot = p->center.y  - p->height;
	//float left = p->center.x - p->width;
	float right = p->center.x + p->width;
	int i = 0;
	if (game->inv[i] == true) {
		if (top >= game->interact[i].center.y -game->interact[i].height
		&& bot <= game->interact[i].center.y+ game->interact[i].height
		&& right == game->interact[i].center.x-game->interact[i].width) {
			game->open[i] = true;
		}
	}
	i = 1;
	if (game->inv[1] == true) {
		if (top >= game->interact[i].center.y -game->interact[i].height
		&& bot <= game->interact[i].center.y+ game->interact[i].height
		&& right == game->interact[i].center.x-game->interact[i].width) {
			game->open[i] = true;
		}
	}
	i = 2;
	if (game->inv[2] == true) {
		if (top >= game->interact[2].center.y -game->interact[2].height
		&& bot <= game->interact[2].center.y+ game->interact[2].height
		&& right == game->interact[2].center.x-game->interact[2].width) {
			game->open[i] = true;
		}
	}
	i = 3;
	if (game->inv[3] == true) {
		if (top >= game->interact[2].center.y -game->interact[2].height
		&& bot <= game->interact[2].center.y+ game->interact[2].height
		&& right == game->interact[2].center.x-game->interact[2].width) {
			game->open[i] = true;
		}
	}
	i = 4;
	if (game->inv[4] == true) {
		if (top >= game->interact[2].center.y -game->interact[2].height
		&& bot <= game->interact[2].center.y+ game->interact[2].height
		&& right == game->interact[2].center.x-game->interact[2].width) {
			game->open[i] = true;
		}
	}
	
}
//my requirement function- key "\"
void text(Game *game) 
{
	glScissor(600,0,600,300);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
	Shape *s = &game->text_box;
	float w, h;
	glColor3ub(15,15,15);
	glPushMatrix();
	w = s->width-25;
	h = s->height;
	glBegin(GL_QUADS);
		glVertex2i(s->center.x-(w+25),s->center.y-(h+25));
		glVertex2i(s->center.x-w-25, s->center.y+h+25);
		glVertex2i(s->center.x+25+ w,s->center.y+ h+25);
		glVertex2i(s->center.x+ w+25,s->center.y-h-25);
	glEnd();
	glColor3ub(50,50,50);
	glBegin(GL_QUADS);
		glVertex2i(s->center.x-w,s->center.y-h);
		glVertex2i(s->center.x-w, s->center.y+h);
		glVertex2i(s->center.x+ w,s->center.y+ h);
		glVertex2i(s->center.x+ w,s->center.y-h);
	glEnd();
	glPopMatrix();
	//print text1
	Rect tutorial;
	Rect space;
	tutorial.bot = 200;
	tutorial.left = 200;
	tutorial.center = 0;
	space.bot = 50;
	space.left = 600;
	space.center = 0;
	ggprint08(&space,10,0x00ffffff,
	"press space to continue");
	switch (game->text_count) {
		case 0: 
			ggprint16(&tutorial,76,0x00ffffff, 
			"The goal of the game is to escape the prison.");
			ggprint16(&tutorial,76,0x00ffffff, 
			"There are 5 keys scattered throught the jail");
			break;
		case 1:
			ggprint16(&tutorial,76,0x00ffffff, 
			"You must avoid the cops, collect the keys, and escape!!");
			break;
		case 2:
			ggprint16(&tutorial,76,0x00ffffff, 
			"Arrow keys to move, space to shoot");
			ggprint16(&tutorial,76,0x00ffffff, 
			"Num 1-7 to switch weapons");
			break;	
	}
}
