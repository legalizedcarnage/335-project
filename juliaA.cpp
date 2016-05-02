//Name: 	Julia Acosta
//Written:	04/27/16
//Modified:	05/02/16
//Project 335: 	Prison Escape
//Design/Layout:Creating the walls for each tile of the game
//		and the layout of the prison cell/hallways etc.
//		Adding  objects in the prison cells. 

#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "main.h"
using namespace std;

void drawobject(Game *game, int i)
{
    Shape *s;
    float w, h;
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
void printtile(Game *game) 
{
    //prison cell 1
    if (game->map[0] == 0 && game->map[1] == 0) {

	//declare bed 1 shape
	game->object[1].width = 200;
	game->object[1].height = 100;
	game->object[1].center.x = 230;
	game->object[1].center.y = 750;

	//declare pillow 1 shape
	game->object[2].width = 30;
	game->object[2].height = 40;
	game->object[2].center.x = 75;
	game->object[2].center.y = 750;

	//declare wall 1 shape
	game->object[3].width = 600;
	game->object[3].height = 12;
	game->object[3].center.x = 600;
	game->object[3].center.y = 892;

	//declare wall 2 shape
	game->object[4].width = 12;
	game->object[4].height = 450;
	game->object[4].center.x = 8;
	game->object[4].center.y = 450;

	//declare wall 3 shape
	game->object[5].width = 600;
	game->object[5].height = 12;
	game->object[5].center.x = 600;
	game->object[5].center.y = 8;
	
	//declare wall 4 shape
        game->object[6].width = 12;
        game->object[6].height = 350;
        game->object[6].center.x = 1192;
        game->object[6].center.y = 600;

	game->num_objects = 7;

	//bed 1
	glColor3ub(69,69,69);
	drawobject(game, 1);
	
	//pillow 1
	glColor3ub(250,250,250);
	drawobject(game, 2);
	
	//walls
	for (int i=3; i<game->num_objects; i++) {
	    glColor3ub(130,130,130);
	    drawobject(game, i);
	}
    }
    //hallway 1
    else if (game->map[0] == 1 && game->map[1] == 0) {

        //declare wall 1 shape
        game->object[1].width = 12;
        game->object[1].height = 400;
        game->object[1].center.x = 8;
        game->object[1].center.y = 650;

        //declare wall 2 shape
        game->object[2].width = 12;
        game->object[2].height = 350;
        game->object[2].center.x = 1192;
        game->object[2].center.y = 600;

	game->num_objects = 3;

	//walls
        for (int i=0; i<game->num_objects; i++) {
            glColor3ub(130,130,130);
	    drawobject(game, i);
        }
    }
    //prison cell 2
    else if (game->map[0] == 2 && game->map[1] == 0) {

	//declare bed 1 shape
        game->object[1].width = 200;
        game->object[1].height = 100;
        game->object[1].center.x = 950;
        game->object[1].center.y = 750;

        //declare pillow 1 shape
        game->object[2].width = 30;
        game->object[2].height = 40;
        game->object[2].center.x = 1100;
        game->object[2].center.y = 750;

        //declare wall 1 shape
        game->object[3].width = 600;
        game->object[3].height = 12;
        game->object[3].center.x = 600;
        game->object[3].center.y = 892;

        //declare wall 2 shape
        game->object[4].width = 12;
        game->object[4].height = 350;
        game->object[4].center.x = 8;
        game->object[4].center.y = 600;

        //declare wall 3 shape
        game->object[5].width = 600;
        game->object[5].height = 12;
        game->object[5].center.x = 600;
        game->object[5].center.y = 8;

        //declare wall 4 shape
        game->object[6].width = 12;
        game->object[6].height = 500;
        game->object[6].center.x = 1192;
        game->object[6].center.y = 500;

        game->num_objects = 7;

        //bed 1
        glColor3ub(69,69,69);
	drawobject(game, 1);
	
	//pillow 1
        glColor3ub(250,250,250);
	drawobject(game, 2);
        
	//walls
        for (int i=3; i<game->num_objects; i++) {
            glColor3ub(130,130,130);
	    drawobject(game, i);
        }

    }
    //hallway 2
    else if (game->map[0] == 1 && game->map[1] == 1) {

	//declare wall 1 shape
        game->object[1].width = 12;
        game->object[1].height = 350;
        game->object[1].center.x = 8;
        game->object[1].center.y = 300;

        //declare wall 2 shape
        game->object[2].width = 12;
        game->object[2].height = 350;
        game->object[2].center.x = 1192;
        game->object[2].center.y = 300;

	//declare wall 3 shape
        game->object[3].width = 600;
        game->object[3].height = 12;
        game->object[3].center.x = 600;
        game->object[3].center.y = 892;

	game->num_objects = 4;

	//walls
        for (int i=0; i<game->num_objects; i++) {
            glColor3ub(130,130,130);
	    drawobject(game, i);
        }

    }
    //prison cell 3
    else if (game->map[0] == 0 && game->map[1] == 1) {

	//declare bed 1 shape
	game->object[1].width = 200;
	game->object[1].height = 100;
	game->object[1].center.x = 230;
	game->object[1].center.y = 150;

	//declare pillow 1 shape
	game->object[2].width = 30;
	game->object[2].height = 40;
	game->object[2].center.x = 75;
	game->object[2].center.y = 150;

	//declare wall 1 shape
	game->object[3].width = 600;
	game->object[3].height = 12;
	game->object[3].center.x = 600;
	game->object[3].center.y = 892;

	//declare wall 2 shape
	game->object[4].width = 12;
	game->object[4].height = 450;
	game->object[4].center.x = 8;
	game->object[4].center.y = 450;

	//declare wall 3 shape
	game->object[5].width = 600;
	game->object[5].height = 12;
	game->object[5].center.x = 600;
	game->object[5].center.y = 8;
	
	//declare wall 4 shape
        game->object[6].width = 12;
        game->object[6].height = 350;
        game->object[6].center.x = 1192;
        game->object[6].center.y = 300;

	game->num_objects = 7;

	//bed 1
	glColor3ub(69,69,69);
	drawobject(game, 1);
	
	//pillow 1
	glColor3ub(250,250,250);
	drawobject(game, 2);
	
	//walls
	for (int i=3; i<game->num_objects; i++) {
	    glColor3ub(130,130,130);
	    drawobject(game, i);
	}

    }
    //prison cell 4
    else if (game->map[0] == 2 && game->map[1] == 1) {

	//declare bed 1 shape
        game->object[1].width = 200;
        game->object[1].height = 100;
        game->object[1].center.x = 950;
        game->object[1].center.y = 150;

        //declare pillow 1 shape
        game->object[2].width = 30;
        game->object[2].height = 40;
        game->object[2].center.x = 1100;
        game->object[2].center.y = 150;

        //declare wall 1 shape
        game->object[3].width = 600;
        game->object[3].height = 12;
        game->object[3].center.x = 600;
        game->object[3].center.y = 892;

        //declare wall 2 shape
        game->object[4].width = 12;
        game->object[4].height = 350;
        game->object[4].center.x = 8;
        game->object[4].center.y = 300;

        //declare wall 3 shape
        game->object[5].width = 600;
        game->object[5].height = 12;
        game->object[5].center.x = 600;
        game->object[5].center.y = 8;

        //declare wall 4 shape
        game->object[6].width = 12;
        game->object[6].height = 500;
        game->object[6].center.x = 1192;
        game->object[6].center.y = 500;

        game->num_objects = 7;

        //bed 1
        glColor3ub(69,69,69);
	drawobject(game, 1);
	
	//pillow 1
        glColor3ub(250,250,250);
	drawobject(game, 2);
        
	//walls
        for (int i=3; i<game->num_objects; i++) {
            glColor3ub(130,130,130);
	    drawobject(game, i);
        }
    }
    else 
	game->num_objects = 0;
}

