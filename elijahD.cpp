//Elijah Davis
//335
//screen transitions and collisions
#include <iostream>
#include "main.h"
using namespace std;
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

	//detect object collisions (BAD! FIX IT!)
	Shape *s;
	for (int i = 0; i < game->num_objects; i++) {
		s = &game->object[i];
		if (p->s.center.y + p->s.height >= s->center.y- s->height
		&& p->s.center.y - p->s.height <= s->center.y + s->height
		&& p->s.center.x  + p->s.width >= s->center.x - s->width
		&& p->s.center.x - p->s.width <= s->center.x + s->width) {
			if (p->velocity.y > 0) {
				p->s.center.y -= p->velocity.y;
				p->velocity.y = 0;
			}
			if (p->velocity.y < 0) {
				p->s.center.y += p->velocity.y;
				p->velocity.y = 0;
			}
			if (p->velocity.x < 0) {
				p->s.center.x -= p->velocity.x;
				p->velocity.x = 0;
			}
			if (p->velocity.x > 0) {
				p->s.center.x += p->velocity.x;
				p->velocity.x = 0;
			}
		}		
	}
	//detect screen collisions
	//floor
	if (p->s.center.y - p->s.height == 0 && p->velocity.y < 0) {
		p->s.center.y = WINDOW_HEIGHT - p->s.height;
		//p->s.center.y = p->s.height;
		//p->velocity.y = 0;
		shiftScreen(game, 'd');
	}
	//roof
	if (p->s.center.y + p->s.height == WINDOW_HEIGHT && p->velocity.y > 0) {
		//p->s.center.y = WINDOW_HEIGHT - p->s.height;
		p->s.center.y = p->s.height;
		//p->velocity.y = 0;
		shiftScreen(game, 'u');
	}
	//left wall
	if (p->s.center.x - p->s.width <= 0 && p->velocity.x < 0) {
		p->s.center.x = WINDOW_WIDTH - p->s.width;
		//p->s.center.x = p->s.width;
		//p->velocity.x = 0;
		shiftScreen(game, 'l');
	}
	//right wall
	if (p->s.center.x + p->s.width >= WINDOW_WIDTH && p->velocity.x > 0) {
		p->s.center.x = p->s.width;
		//p->s.center.x = WINDOW_WIDTH - p->s.width;
		//p->velocity.x = 0;
		shiftScreen(game, 'r');
	}
	
}
