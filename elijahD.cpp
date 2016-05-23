//Elijah Davis
//cs 335
//started 4/22/16
//screen transitions and collision detection of player
//and bullets with each other, the walls, and objects
//started 5/19/16
//interactable objects such as walls and gates that need to be matched with correct keys
#include <iostream>
#include <stdlib.h>
#include <GL/glx.h>

#include "main.h"
#include "miguelT.h"
#include "marioH.h"
using namespace std;
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
	std::cout << game->map[0]  << ", " << game->map[1] << endl;
	if(!game->enemies[game->map[0]+1][game->map[1]+1][0].enemiesInit)	
		initEnemies(game, game->map[0], game->map[1], game->current_enemies);
}
void Player_Object(Game *game, Player *p, Shape *objects, int num)
{
	p = &game->player;
	//defined edges
	float top = p->s.center.y  + p->s.height;
	float bot = p->s.center.y  - p->s.height;
	float left = p->s.center.x - p->s.width;
	float right = p->s.center.x + p->s.width;
	
	Shape *s;
	for (int i = 0; i < num; i++) {
	//for (int i = 0; i < game->num_objects; i++) {
		//s = &game->object[i];
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
void playerCollision(Game *game)
{
	Player *p;
	p = &game->player;
	//defined edges
	void key(Game *game);
	key(game);
	float top = p->s.center.y  + p->s.height;
	float bot = p->s.center.y  - p->s.height;
	float left = p->s.center.x - p->s.width;
	float right = p->s.center.x + p->s.width;

	//detect object collisions //added enemy collision
	Player_Object(game, &game->player,game->object,game->num_objects);
	for (int i = 0; i<game->num_enemies; i++)
		Player_Object(game
			, &game->enemies[game->map[0]][game->map[1]][i]
			,game->object
			,game->num_objects);
	//detect screen collisions
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
	//player-enemy collision
	for ( int i = 0; i < 2/*game->num_enemies*/; i++) {
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
		if (top >= enemy_b &&
		bot <= enemy_t &&
		left <= enemy_r &&
		right >= enemy_l) {
			p->health--;
		//knocked back when hit enemy
			int min_distY = 100;
			int min_distX = 100;
			for (int j = 0; j < game->num_objects; j++) {
				//ceiling
				if (abs(top - (game->object[j].center.y - 
				game->object[j].height))  >= 
				abs(.5*(p->s.center.y - e->s.center.y))) {
					if (abs(p->s.center.y-e->s.center.y) 
					<= abs(min_distY)) {
						min_distY = 
						.5*( p->s.center.y - e->s.center.y);
						cout << "enemy closer than wallY" << endl;
					}
				
				} else {
					min_distY =
					-(top - (game->object[j].center.y - 
					game->object[j].height));
					cout << "top" << endl;
				}
				//floor
				if (abs(bot - (game->object[j].center.y + 
				game->object[j].height)) >=
				abs(.5*(p->s.center.y - e->s.center.y))) {
					if (abs(p->s.center.y-e->s.center.y) 
					<= abs(min_distY)) {
						min_distY =
						.5*(p->s.center.y - e->s.center.y);
					}
				} else {
					min_distY =
					-(bot - (game->object[j].center.y +
					game->object[j].height));
					cout << "bot" << endl;
				}
				//sides
				if (abs(right - (game->object[j].center.x - 
				game->object[j].width))  >= 
				abs(p->s.center.x - e->s.center.x)) {
					if (abs(p->s.center.x-e->s.center.x) 
					<= abs(min_distX)) {
						min_distX = 
						(p->s.center.x - e->s.center.x);
						cout << "enemy closer than wallX" << endl;
					}
				} else {	
					min_distX =
					-(right - (game->object[j].center.x - 
					game->object[j].width));
					cout << "right" << endl;
				}
				if (abs(left - (game->object[j].center.x + 
				game->object[j].width)) >=
				abs((p->s.center.x - e->s.center.x))) {
					if (abs(p->s.center.x-e->s.center.x) 
					<= abs(min_distX)) {
						min_distX =
						(p->s.center.x - e->s.center.x);
					}
				} else {
					min_distX =
					-(left - (game->object[j].center.x +
					game->object[j].width));
					cout << "left" << endl;
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
	//Player_Object(game, &game->player);
	Player_Object(game, &game->player,game->object,game->num_objects);
}
void Respawn(Game *game)
{	
	game->map[0] = 0;
	game->map[1] = 0;
	game->player.health = Start_HP;	
	initPlayer(game);
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
				cout << "hit enemy" << endl;
		
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
				cout << "hit a wall" << endl;
				break;
			}
		}
		//check for off-screen
		if (p->s.center.x > WINDOW_WIDTH + p->s.width) {
			std::cout << "off screen" << std::endl;
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.x < 0.0) {
			std::cout << "off screen" << std::endl;
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.y > WINDOW_HEIGHT + p->s.height) {
			std::cout << "off screen" << std::endl;
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.y < 0.0) {
			std::cout << "off screen" << std::endl;
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
	game->keys[0].width = 5;
	game->keys[0].height = 3;

	game->keys[1].center.x = 1000;
	game->keys[1].center.y = 200;
	game->keys[1].width = 5;
	game->keys[1].height = 3;

	game->keys[2].center.x = 1000;
	game->keys[2].center.y = 200;
	game->keys[2].width = 5;
	game->keys[2].height = 3;

	game->keys[3].center.x = 100;
	game->keys[3].center.y = 800;
	game->keys[3].width = 5;
	game->keys[3].height = 3;

	game->keys[4].center.x = 1000;
	game->keys[4].center.y = 200;
	game->keys[4].width = 5;
	game->keys[4].height = 3;
	
}
void Print_keys(Game *game) 
{
	game->key_num = -1;
	//check if key should be printed on tile
	if (game->map[0] == 0 && game->map[1] ==1) {
		game->key_num = 0;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
	}
	if (game->map[0] == 4 && game->map[1] ==-1) {
		game->key_num = 1;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
	}	
	if (game->map[0] == 5 && game->map[1] ==0) {
		game->key_num = 2;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
	}	
	if (game->map[0] == 3 && game->map[1] ==2) {
		game->key_num = 3;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
	}	
	if (game->map[0] == 5 && game->map[1] ==2) {
		game->key_num = 4;
		if (game->inv[game->key_num] == true) {
			game->key_num = -1;
		}
	}	
	if (game->key_num >= 0) {
		Shape *s;
		float w, h;
		s = &game->keys[game->key_num];
		glColor3ub(10,10,10);
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

void interact(Game *game) 
{
	//Player_Object(game, &game->player, game->interact, game->num_interact);	
}

