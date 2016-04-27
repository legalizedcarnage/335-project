//Julia Acosta
//335
//project- Prison Escape

#include <iostream>
#include "main.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
using namespace std;

//void printtile(Game *game);

void printtile(Game *game) 
{
    if (game->map[0] == 0 && game->map[0] == 0) {
	Shape *s;
	float w, h;

	//declare bed 1 shape
	game->object[1].width = 80;
	game->object[1].height = 40;
	game->object[1].center.x = 125;
	game->object[1].center.y = 820;

	//declare pillow 1 shape
	game->object[2].width = 20;
	game->object[2].height = 20;
	game->object[2].center.x = 85;
	game->object[2].center.y = 820;

	//declare wall 1 shape
	game->object[3].width = 600;
	game->object[3].height = 5;
	game->object[3].center.x = 600;
	game->object[3].center.y = 892;

	//declare wall 2 shape
	game->object[4].width = 5;
	game->object[4].height = 450;
	game->object[4].center.x = 8;
	game->object[4].center.y = 450;

	//declare wall 3 shape
	game->object[5].width = 600;
	game->object[5].height = 5;
	game->object[5].center.x = 600;
	game->object[5].center.y = 8;
	
	//declare wall 4 shape
        game->object[6].width = 5;
        game->object[6].height = 350;
        game->object[6].center.x = 1192;
        game->object[6].center.y = 600;

	//bed 1
	glColor3ub(191,191,191);
	s = &game->object[1];
	glPushMatrix();
	glTranslatef(s->center.x, s->center.y, s->center.z);
	w = s->width;
	h = s->height;
	glBegin(GL_QUADS);
	glVertex2i(-w,-h);
	glVertex2i(-w, h);
	glVertex2i( w, h);
	glVertex2i( w,-h);
	glEnd();
	glPopMatrix();

	//pillow 1
	glColor3ub(250,250,250);
	s = &game->object[2];
	glPushMatrix();
	glTranslatef(s->center.x, s->center.y, s->center.z);
	w = s->width;
	h = s->height;
	glBegin(GL_QUADS);
	glVertex2i(-w,-h);
	glVertex2i(-w, h);
	glVertex2i( w, h);
	glVertex2i( w,-h);
	glEnd();
	glPopMatrix();

	//walls
	for (int i=3; i<7; i++) {
	    glColor3ub(61,61,61);
	    s = &game->object[i];
	    glPushMatrix();
	    glTranslatef(s->center.x, s->center.y, s->center.z);
	    w = s->width;
	    h = s->height;
	    glBegin(GL_QUADS);
	    glVertex2i(-w,-h);
	    glVertex2i(-w, h);
	    glVertex2i( w, h);
	    glVertex2i( w,-h);
	    glEnd();
	    glPopMatrix();
	}
    }
    if (game->map[1] == 0 && game->map[1] == 0) {
	Shape *s;
	float w, h;

	//declare wall 1 shape
        game->object[7].width = 600;
        game->object[7].height = 5;
        game->object[7].center.x = 600;
        game->object[7].center.y = 892;

        //declare wall 2 shape
        game->object[8].width = 5;
        game->object[8].height = 450;
        game->object[8].center.x = 8;
        game->object[8].center.y = 450;

        //declare wall 3 shape
        game->object[9].width = 600;
        game->object[9].height = 5;
        game->object[9].center.x = 600;
        game->object[9].center.y = 8;

        //declare wall 4 shape
        game->object[10].width = 5;
        game->object[10].height = 350;
        game->object[10].center.x = 1192;
        game->object[10].center.y = 600;

	//walls
        for (int i=7; i<11; i++) {
            glColor3ub(61,61,61);
            s = &game->object[i];
            glPushMatrix();
            glTranslatef(s->center.x, s->center.y, s->center.z);
            w = s->width;
            h = s->height;
            glBegin(GL_QUADS);
            glVertex2i(-w,-h);
            glVertex2i(-w, h);
            glVertex2i( w, h);
            glVertex2i( w,-h);
            glEnd();
            glPopMatrix();
        }


    }

}

