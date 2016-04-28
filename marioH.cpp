//Author:Mario Hernandez
//Purpose: to render the main menu and functionality of the menu buttons
#include <iostream>
#include "main.h"
#include "marioH.h"
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

using namespace std;
//int mainMenuCursor(XEvent *e,Game * game);

void displayMenu(Game * game)
{
    int cursorPos = 0;
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
    //
    glColor3ub(0,140,0);
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
    //mainMenuCursor(XEvent *e,Game * game);
    game->state = 1;
}

int mainMenuCursor(XEvent *e,Game * game) {
    if(game->state ==0) {
	if (e->type == KeyPress) {
	    int key = XLookupKeysym(&e->xkey, 0);
                if (key == XK_Escape) {
		    return 1;
		}
		switch(key) {
		    case XK_Up:
			break;
		    case XK_Down:
			break;
		}
	}
	if ( e->type == KeyRelease) {
	    int key = XLookupKeysym(&e->xkey, 0);
                switch(key) {
		    case XK_Up:
			break;
		    case XK_Down:
			break;
		}
	}
    }
    game->state = 1;
    return 0;
}
	
