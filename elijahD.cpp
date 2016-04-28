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
	//detect object collisions
	/*Shape *s;
	for (int i; i < game->num_objects; i++) {
		s = &game->object[i];
		
	}*/
	//detect screen collisions
	Player *p;
	p = &game->player;
	//floor
	if (p->s.center.y - p->s.height == 0 && p->velocity.y < 0) {
		p->s.center.y = p->s.height;
		p->velocity.y = 0;
		shiftScreen(game, 'd');
	}
	//roof
	if (p->s.center.y + p->s.height == WINDOW_HEIGHT && p->velocity.y > 0) {
		p->s.center.y = WINDOW_HEIGHT - p->s.height;
		p->velocity.y = 0;
		shiftScreen(game, 'u');
	}
	//left wall
	if (p->s.center.x - p->s.width <= 0 && p->velocity.x < 0) {
		p->s.center.x = p->s.width;
		p->velocity.x = 0;
		shiftScreen(game, 'l');
	}
	//right wall
	if (p->s.center.x + p->s.width >= WINDOW_WIDTH && p->velocity.x > 0) {
		p->s.center.x = WINDOW_WIDTH - p->s.width;
		p->velocity.x = 0;
		shiftScreen(game, 'r');
	}
	
}
