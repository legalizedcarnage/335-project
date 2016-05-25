//Name: 	Julia Acosta
//Written:	04/27/16
//Modified:	05/25/16
//Project 335: 	Prison Escape
//Design/Layout:Creating the walls for each tile of the game
//		and the layout of the prison cell/hallways etc.
//		Adding  objects in the prison cells. Adding a map
//		image for the function. 

#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "main.h"
#include "ppm.h"
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
void declareobject(Game *game, int i, int a, int b, int c, int d)
{
    game->object[i].width = a;
    game->object[i].height = b;
    game->object[i].center.x = c;
    game->object[i].center.y = d;

}
void map(Game *game) 
{
    Ppmimage *mapImage = NULL;
    GLuint mapTexture;
    
    mapImage = ppm6GetImage("map.ppm");
    glGenTextures(1, &mapTexture);
    //map image
    glBindTexture(GL_TEXTURE_2D, mapTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	mapImage->width, mapImage->height,
	0, GL_RGB, GL_UNSIGNED_BYTE, mapImage->data);
    
    glBindTexture(GL_TEXTURE_2D, mapTexture);
    glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, WINDOW_HEIGHT);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(WINDOW_WIDTH, 0);
	glEnd();
}
void printtile(Game *game) 
{
    //prison cell 1
    if (game->map[0] == 0 && game->map[1] == 0) {
	//bed 1 shape  
	declareobject(game, 1, 200, 100, 230, 750);

	//pillow 1 shape
	declareobject(game, 2, 30, 40, 75, 750);

	//wall 1-4 shapes
	declareobject(game, 3, 600, 12, 600, 892);
	declareobject(game, 4, 12, 450, 8, 450);
	declareobject(game, 5, 600, 12, 600, 8);
	declareobject(game, 6, 12, 350, 1192, 600);
	
	//jail cell gate
/*	int gate = 1;
	if (gate == 1) {
		declareobject(game, 7, 12, 10, 1192, 200);
		declareobject(game, 8, 12, 10, 1192, 150);
		declareobject(game, 9, 12, 10, 1192, 100);
		declareobject(game, 10, 12, 10, 1192, 50);
	}
	else 
	    gate = 2;
	//card
	int card = 1;
	if (card == 1) {
		declareobject(game, 11, 10, 10, 1000, 800);
		glColor3ub(255,0,0);
		drawobject(game, 11);
	}
	if () {
	   card = 0;	
	   gate = 0;
	}
*/
	game->num_objects = 11; //7 or 11;

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
	//wall 1-2 shapes
	declareobject(game, 1, 12, 400, 8, 650);
	declareobject(game, 2, 12, 350, 1192, 600);

	game->num_objects = 3;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //prison cell 2
    else if (game->map[0] == 2 && game->map[1] == 0) {
	//bed 1 shape
	declareobject(game, 1, 200, 100, 950, 750);

	//pillow 1 shape
	declareobject(game, 2, 30, 40, 1100, 750);

	//wall 1-4 shapes
	declareobject(game, 3, 600, 12, 600, 892);
	declareobject(game, 4, 12, 350, 8, 600);
	declareobject(game, 5, 600, 12, 600, 8);
	declareobject(game, 6, 12, 500, 1192, 500);

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
	//wall 1-3 shape
	declareobject(game, 1, 12, 350, 8, 300);
	declareobject(game, 2, 12, 350, 1192, 300);
	declareobject(game, 3, 600, 12, 600, 892);

	game->num_objects = 4;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}

    }
    //prison cell 3
    else if (game->map[0] == 0 && game->map[1] == 1) {
	//bed 1 shape
	declareobject(game, 1, 200, 100, 230, 150);

	//pillow 1 shape
	declareobject(game, 2, 30, 40, 75, 150);

	//wall 1-4 shapes
	declareobject(game, 3, 600, 12, 600, 892);
	declareobject(game, 4, 12, 450, 8, 450);
	declareobject(game, 5, 600, 12, 600, 8);
	declareobject(game, 6, 12, 350, 1192, 300);

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
	declareobject(game, 1, 200, 100, 950, 150);

	//declare pillow 1 shape
	declareobject(game, 2, 30, 40, 1100, 150);

	//wall 1-4 shapes
	declareobject(game, 3, 600, 12, 600, 892);
	declareobject(game, 4, 12, 350, 8, 300);
	declareobject(game, 5, 600, 12, 600, 8);
	declareobject(game, 6, 12, 500, 1192, 500);

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
    //hallway 3
    else if (game->map[0] == 1 && game->map[1] == -1) {
	//wall 1-3 shapes
	declareobject(game, 1, 12, 350, 8, 300);
	declareobject(game, 2, 12, 350, 1192, 300);
	declareobject(game, 3, 600, 12, 600, 8);

	game->num_objects = 4;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //shower
    else if (game->map[0] == 0 && game->map[1] == -1) {
	//wall 1-4 shapes
	declareobject(game, 1, 600, 12, 600, 892);
	declareobject(game, 2, 12, 450, 8, 450);
	declareobject(game, 3, 600, 12, 600, 8);
	declareobject(game, 4, 12, 350, 1192, 300);

	game->num_objects = 5;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //security guard office
    else if (game->map[0] == 2 && game->map[1] == -1) {
	//wall 1-5 shapes
	declareobject(game, 1, 600, 12, 600, 892);
	declareobject(game, 2, 12, 350, 8, 300);
	declareobject(game, 3, 600, 12, 600, 8);
	declareobject(game, 4, 12, 350, 1192, 300);
	declareobject(game, 5, 480, 12, 750, 650);

	game->num_objects = 6;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //level 2
    else if (game->map[0] == 3 && game->map[1] == -1) {
	//wall 1-6 shapes
	declareobject(game, 1, 400, 12, 200, 892);
	declareobject(game, 2, 12, 350, 8, 300);
	declareobject(game, 3, 600, 12, 600, 8);
	declareobject(game, 4, 12, 350, 1192, 300);
	declareobject(game, 5, 12, 350, 600, 600);
	declareobject(game, 6, 180, 12, 1050, 892);

	game->num_objects = 7;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //warden's office
    else if (game->map[0] == 4 && game->map[1] == -1) {
	//wall 1-4 shapes
	declareobject(game, 1, 600, 12, 600, 892);
	declareobject(game, 2, 12, 350, 8, 300);
	declareobject(game, 3, 600, 12, 600, 8);
	declareobject(game, 4, 12, 500, 1192, 500);

	game->num_objects = 5;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //Level 3
    else if (game->map[0] == 3 && game->map[1] == 0) {
	//Tower 1/wall 1-4 shape
	declareobject(game, 1, 300, 12, 200, 892);
	declareobject(game, 2, 12, 450, 8, 450);
	declareobject(game, 3, 400, 12, 200, 8);
	declareobject(game, 4, 12, 200, 1192, 150);
	declareobject(game, 5, 180, 12, 1050, 8);
	declareobject(game, 6, 250, 12, 1050, 892);
	declareobject(game, 7, 12, 200, 1192, 800);

	game->num_objects = 8;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //bridge 1
    else if (game->map[0] == 3 && game->map[1] == 1) {
	//bridge 1
	declareobject(game, 1, 300, 12, 200, 892);
	declareobject(game, 2, 12, 450, 8, 450);
	declareobject(game, 3, 300, 12, 200, 8);
	declareobject(game, 4, 12, 200, 1192, 150);
	declareobject(game, 5, 250, 12, 1050, 8);
	declareobject(game, 6, 250, 12, 1050, 892);
	declareobject(game, 7, 12, 200, 1192, 800);

	game->num_objects = 8;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //Tower 2
    else if (game->map[0] == 3 && game->map[1] == 2) {
	//wals 1-4 shape
	declareobject(game, 1, 600, 12, 600, 892);
	declareobject(game, 2, 12, 450, 8, 450);
	declareobject(game, 3, 300, 12, 200, 8);
	declareobject(game, 4, 12, 200, 1192, 150);
	declareobject(game, 5, 250, 12, 1050, 8);
	declareobject(game, 6, 12, 200, 1192, 800);

	game->num_objects = 7;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //bridge 2
    else if (game->map[0] == 4 && game->map[1] == 0) {
	//walls 1-7 shape
	declareobject(game, 1, 300, 12, 200, 892);
	declareobject(game, 2, 12, 200, 8, 150);
	declareobject(game, 3, 600, 12, 600, 8);
	declareobject(game, 4, 12, 200, 1192, 150);
	declareobject(game, 5, 12, 200, 8, 800);
	declareobject(game, 6, 250, 12, 1050, 892);
	declareobject(game, 7, 12, 200, 1192, 800);

	game->num_objects = 8;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //yard
    else if (game->map[0] == 4 && game->map[1] == 1) {
	//walls 1-8 shape
	declareobject(game, 1, 300, 12, 200, 892);
	declareobject(game, 2, 12, 200, 8, 150);
	declareobject(game, 3, 300, 12, 200, 8);
	declareobject(game, 4, 12, 200, 1192, 150);
	declareobject(game, 5, 12, 200, 8, 800);
	declareobject(game, 6, 250, 12, 1050, 892);
	declareobject(game, 7, 12, 200, 1192, 800);
	declareobject(game, 8, 250, 12, 1050, 8);

	game->num_objects = 9;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //bridge 3
    else if (game->map[0] == 4 && game->map[1] == 2) {
	//walls 1-7 shape
	declareobject(game, 1, 600, 12, 600, 892);
	declareobject(game, 2, 12, 200, 8, 150);
	declareobject(game, 3, 300, 12, 200, 8);
	declareobject(game, 4, 12, 200, 1192, 150);
	declareobject(game, 5, 12, 200, 8, 800);
	declareobject(game, 6, 12, 200, 1192, 800);
	declareobject(game, 7, 250, 12, 1050, 8);

	game->num_objects = 8;

	//walls
	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(130,130,130);
		drawobject(game, i);
	}
    }
    //Tower 4
    else if (game->map[0] == 5 && game->map[1] == 0) {
	//walss 1-6 shape
        declareobject(game, 1, 300, 12, 200, 892);
        declareobject(game, 2, 12, 200, 8, 150);
        declareobject(game, 3, 600, 12, 600, 8);
        declareobject(game, 4, 12, 600, 1192, 600);
        declareobject(game, 5, 12, 200, 8, 800);
        declareobject(game, 6, 250, 12, 1050, 892);

        game->num_objects = 7;

        //walls
        for (int i=0; i<game->num_objects; i++) {
                glColor3ub(130,130,130);
                drawobject(game, i);
	}
    }	
    //Bridge 4
    else if (game->map[0] == 5 && game->map[1] == 1) {
	//walls 1-8 shape
        declareobject(game, 1, 300, 12, 200, 892);
        declareobject(game, 2, 12, 200, 8, 150);
        declareobject(game, 3, 300, 12, 200, 8);
        declareobject(game, 4, 12, 200, 8, 800);
        declareobject(game, 5, 250, 12, 1050, 892);
        declareobject(game, 6, 250, 12, 1050, 8);

        game->num_objects = 7;

        //walls
        for (int i=0; i<game->num_objects; i++) {
                glColor3ub(130,130,130);
                drawobject(game, i);
	}
	declareobject(game, 1, 22, 200, 1192, 150);
	declareobject(game, 2, 22, 200, 1192, 800);

	game->num_objects = 3;

	for (int i=0; i<game->num_objects; i++) {
		glColor3ub(0, 255, 127);
		drawobject(game, i);
	}
    }
    //Tower 3
    else if (game->map[0] == 5 && game->map[1] == 2) {
	//walls 1-6 shape
        declareobject(game, 1, 600, 12, 600, 892);
        declareobject(game, 2, 12, 200, 8, 150);
        declareobject(game, 3, 300, 12, 200, 8);
        declareobject(game, 4, 12, 600, 1192, 600);
        declareobject(game, 5, 12, 200, 8, 800);
        declareobject(game, 6, 250, 12, 1050, 8);

        game->num_objects = 7;

        //walls
        for (int i=0; i<game->num_objects; i++) {
                glColor3ub(130,130,130);
                drawobject(game, i);
	}
    }	
    else 
	game->num_objects = 0;
}

