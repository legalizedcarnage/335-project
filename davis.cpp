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
    
