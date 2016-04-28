#include <iostream>
#include "main.h"
#include <GL/glx.h>

using namespace std;
void displayMenu(Game * game)
{
    cout << "menu" << endl;
    glClearColor(0.5,0.5,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    game->state = 1;
}
