//Elijah Davis
//cs 335
//started 4/22/16
//screen transitions and collision detection of player
//and bullets with each other, the walls, and objects
#include <iostream>
#include "main.h"
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

}
void playerCollision(Game *game)
{
	Player *p;
	p = &game->player;

	//detect object collisions 
	Shape *s;
	for (int i = 0; i < game->num_objects; i++) {
		s = &game->object[i];
		//defined edges
		float top = p->s.center.y  + p->s.height;
		float bot = p->s.center.y  - p->s.height;
		float left = p->s.center.x - p->s.width;
		float right = p->s.center.x + p->s.width;

		if (top >= s->center.y - s->height
		&& top <= s->center.y + s->height
		&& left < s->center.x + s->width
		&& right > s->center.x - s->width
		&& p->velocity.y > 0 ) {
			p->velocity.y = 0;
		} 
		
		if (bot >= s->center.y - s->height
		&& bot <= s->center.y + s->height
		&& left < s->center.x + s->width
		&& right > s->center.x - s->width
		&& p->velocity.y < 0 ) {
			p->velocity.y = 0;
		} 
		if (left >= s->center.x - s->width
		&& left <= s->center.x + s->width
		&& bot < s->center.y + s->height
		&& top > s->center.y - s->height
		&& p->velocity.x < 0 ) {
			p->velocity.x = 0;
		} 
		if (right >= s->center.x - s->width
		&& right <= s->center.x + s->width
		&& bot < s->center.y + s->height
		&& top > s->center.y - s->height
		&& p->velocity.x > 0 ) {
			p->velocity.x = 0;
		} 
		
	}
	//detect screen collisions
	//floor
	if (p->s.center.y - p->s.height == 0 && p->velocity.y < 0) {
		p->s.center.y = WINDOW_HEIGHT - p->s.height;
		//change when multiple weapons implemented
		game->knife.k.center.x = p->s.center.x + 20;
		game->knife.k.center.y = p->s.center.y +5;
		//
		shiftScreen(game, 'd');
	}
	//roof
	if (p->s.center.y + p->s.height == WINDOW_HEIGHT && p->velocity.y > 0) {
		p->s.center.y = p->s.height;
		//
		game->knife.k.center.x = p->s.center.x + 20;
		game->knife.k.center.y = p->s.center.y +5;
		//
		shiftScreen(game, 'u');
	}
	//left wall
	if (p->s.center.x - p->s.width <= 0 && p->velocity.x < 0) {
		p->s.center.x = WINDOW_WIDTH - p->s.width;
		//
		game->knife.k.center.x = p->s.center.x + 20;
		game->knife.k.center.y = p->s.center.y +5;
		//
		shiftScreen(game, 'l');
	}
	//right wall
	if (p->s.center.x + p->s.width >= WINDOW_WIDTH && p->velocity.x > 0) {
		p->s.center.x = p->s.width;
		//
		game->knife.k.center.x = p->s.center.x + 20;
		game->knife.k.center.y = p->s.center.y +5;
		//
		shiftScreen(game, 'r');
	}
	//player-enemy collision
	
	
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
			cout << "shot" << endl;
			//decrease lives once lives implemented
			play->health--;
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
