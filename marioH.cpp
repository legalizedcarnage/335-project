//Author:Mario Hernandez
//Purpose: to render the main menu and functionality of the menu buttons
//Written:	4/27/16
//Modified:	5/11/16
//Progress, Currently have the basic main menu working by jumping into the game
// and a quit button. Also working on a pause menu with basic button functions
// and leaving room to include inventory functionality and option menu
// functionality
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

void hudDisplay(Game * game) 
{
	glColor3ub(100,0,0);
	declareobject(game,game->num_objects,150,10,250,860);
	drawobject(game,game->num_objects);
	Rect health;
	health.bot = 870;
	health.left = 210;
	health.center = 0;
	ggprint16(&health, 76, 0x00ffffff, "Health Bar");
}

int mainMenuCursor(XEvent *e,Game * game)
{
	if (game->state ==0) {
		if (e->type == KeyPress) {
			int key = XLookupKeysym(&e->xkey, 0);
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

void pauseMenuCursor(XEvent *e,Game * game)
{
        if (game->state == 2) {
                if (e->type == KeyPress) {
                        int key = XLookupKeysym(&e->xkey, 0);
                        if (key == XK_Escape) {
			    game->state = 0;
                        }
                        if (key == XK_Up) {
                                cursorPos--;
                                if (cursorPos < 0) {
                                        cursorPos = 3;
                                }
                        }
                        if (key == XK_Down) {
                                cursorPos++;
                                if (cursorPos > 3) {
                                        cursorPos = 0;
                                }
                        }
                        if (key == XK_space || key == 65293) {
                                switch(cursorPos) {
                                        case 0:
                                        game->state = 1; //play button case
                                        break;
					case 1:
					//Check Inventory button case
					break;
					case 2:
					//Change Settings button case
					break;
                                        case 3:
                                        game->state = 0; // quit button case
					cursorPos = 0;
                                        break;
                                }
                        }
                }
        }
}


void pauseMenu(Game * game) 
{
	glClearColor(0.5,0.5,0.5,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
        glColor3ub(100,60,200);
        declareobject(game,1,150,50,250+5*65,1100-5*60);
	declareobject(game,2,150,50,250+5*65,950-5*60);
	declareobject(game,3,150,50,250+5*65,800-5*60);
	declareobject(game,4,150,50,250+5*65,650-5*60);
        drawobject(game,1);
	drawobject(game,2);
	drawobject(game,3);
	drawobject(game,4);
	
	Rect gButton;
	Rect iButton;
	Rect sButton;
        Rect qButton;

        gButton.bot = 790;
        gButton.left = 500;
        gButton.center = 0;
        if (cursorPos ==0) {
                ggprint16(&gButton, 76, 0x00ffffff, "Return to Game");
        }
        else
        	ggprint16(&gButton, 76, 0x00000000, "Return to Game");

	iButton.bot = 640;
	iButton.left = 500;
	iButton.center = 0;
	if (cursorPos == 1) {
		ggprint16(&iButton, 76, 0x00ffffff, "Check Inventory");
	}
	else
		ggprint16(&iButton, 76, 0x00000000, "Check Inventory");
	
	sButton.bot = 490;
	sButton.left = 505;
	sButton.center = 0;
	if (cursorPos == 2) {
		ggprint16(&sButton, 76, 0x00ffffff, "Change Settings");
	}
	else
		ggprint16(&sButton, 76, 0x00000000, "Change Settings");
        qButton.bot = 350;
        qButton.left = 480;
        qButton.center = 0;
        if (cursorPos == 3) {
                ggprint16(&qButton, 76, 0x00ffffff, "Return to Main Menu");
        }
        else
        ggprint16(&qButton, 76, 0x00000000, "Return to Main Menu");	
}

