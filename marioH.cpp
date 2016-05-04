//Author:Mario Hernandez
//Purpose: to render the main menu and functionality of the menu buttons
#include <iostream>
#include "main.h"
#include "marioH.h"
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
    float w,h;
    cout << "menu" << endl;
    glClearColor(0.5,0.5,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    game->button1.height = 50;
    game->button1.width = 150;
    game->button2.height = 50;
    game->button2.width = 150;
    game->button1.center.x = 250 + 5*65; 
    game->button1.center.y = 800 - 5*60;
    game->button2.center.x = 250 + 5*65;
    game->button2.center.y = 650 - 5*60;
    glColor3ub(0,60,200);
    Shape *s, *r;
    s = &game->button1;
    r = &game->button2;

    glPushMatrix(); //push and pull the play button
    glTranslatef(s->center.x, s->center.y,s->center.z);
    w = s->width;
    h = s->height;
    glBegin(GL_QUADS);
    	glVertex2i(-w,-h);
    	glVertex2i(-w, h);
    	glVertex2i( w, h);
    	glVertex2i( w,-h);
    glEnd();
    glPopMatrix();
    
    glPushMatrix(); //push and pull quit button
    glTranslatef(r->center.x, r->center.y,r->center.z);
    w = s->width;
    h = s->height;
    glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w, h);
        glVertex2i( w, h);
        glVertex2i( w,-h);
    glEnd();
    glPopMatrix();

    //Rect pButton;
    Rect pButton;
    Rect qButton;
    pButton.bot = 500;
    pButton.left = 520;
    pButton.center = 0;
    if(cursorPos ==0) {
	ggprint16(&pButton, 76, 0x00ffffff, "Play Game");
    }
    else
	ggprint16(&pButton, 76, 0x00000000, "Play Game");
    qButton.bot = 350;
    qButton.left = 520;
    qButton.center = 0;
    if(cursorPos ==1) {
	ggprint16(&qButton, 76, 0x00ffffff, "Quit Game");
    }
    else
	ggprint16(&qButton, 76, 0x00000000, "Quit Game");
    //game->state = 1;
}

int mainMenuCursor(XEvent *e,Game * game) {
    //int cursorPos = 0;
    if(game->state ==0) {
	if (e->type == KeyPress) {
	    int key = XLookupKeysym(&e->xkey, 0);
                if (key == XK_Escape) {
		    return 1;
		}
		if (key == XK_Up) {
		    cursorPos--;
		    //change color of text
		    if (cursorPos < 0) {
			cursorPos = 1;
		    }
		}
		if (key == XK_Down) {
		    cursorPos++;
		    //change color of text
		    if (cursorPos > 1) {
			cursorPos = 0;
		    }
		}
		if(key == XK_space) {
		    switch(cursorPos) {
			case 0:
			    game->state = 1; //play button case
			    break;
			case 1:
			    return 1; // quit button case
			    break;
		    }
		}
		//return 0;
	}
    }
    return 0;
}
	
