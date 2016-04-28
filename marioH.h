//Author: Mario Hernandez
//purpose: .h file for the menu cpp file
#ifndef MARIO_H
#define MARIO_H
#include "main.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>

struct M_Shape {
    float width, height;
};

struct MainMenu {
    M_Shape button;
};

void displayMenu(Game * game);
int mainMenuCursor(XEvent *e,Game * game);
#endif
