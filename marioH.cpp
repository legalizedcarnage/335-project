//Author:Mario Hernandez
//Purpose: to render the main menu and functionality of the menu buttons
//Written:	4/27/16
//Modified:	5/6/16
#include <iostream>
#include "main.h"
#include "marioH.h"
#include "juliaA.h"
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
extern "C" {
#include "fonts.h"
}

using namespace std;
int cursorPos = 0;
void displayMenu(Game * game)
{
	glClearColor(0.5,0.5,0.5,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0,60,200);
	declareobject(game,1,150,50,250+5*65,800-5*60);//play button
	declareobject(game,2,150,50,250+5*65,650-5*60);//quit button
	glColor3ub(100,0,0);
	//declareobject(game,3,150,20,100,100);
	drawobject(game,1);
	drawobject(game,2);
	Rect pButton;
	Rect qButton;
	pButton.bot = 500;
	pButton.left = 520;
	pButton.center = 0;
	if (cursorPos ==0) {
		ggprint16(&pButton, 76, 0x00ffffff, "Play Game");
		
	}
	else
	ggprint16(&pButton, 76, 0x00000000, "Play Game");
	qButton.bot = 350;
	qButton.left = 520;
	qButton.center = 0;
	if (cursorPos ==1) {
		ggprint16(&qButton, 76, 0x00ffffff, "Quit Game");
		
	}
	else
	ggprint16(&qButton, 76, 0x00000000, "Quit Game");
}

int mainMenuCursor(XEvent *e,Game * game)
{
	if (game->state ==0) {
		if (e->type == KeyPress) {
			int key = XLookupKeysym(&e->xkey, 0);
			cout << key << endl;
			if (key == XK_Escape) {
				return 1;
			
			}
			if (key == XK_Up) {
				cursorPos--;
				if (cursorPos < 0) {
					cursorPos = 1;
				
				}
			}
			if (key == XK_Down) {
				cursorPos++;
				if (cursorPos > 1) {
					cursorPos = 0;
				
				}
			}
			if (key == XK_space || key == 65293) {
				switch(cursorPos) {
					case 0:
					game->state = 1; //play button case
					break;
					case 1:
					return 1; // quit button case
					break;
				}
			}
		}
	}
	return 0;
	
}
	
