
//Author:Mario Hernandez
//Purpose: to render the main menu and functionality of the menu buttons
//Written:	4/27/16
//Modified:	5/25/16
//Progress, Currently have the basic main menu working by jumping into the game
// and a quit button. Also working on a pause menu with basic button functions
// and leaving room to include inventory functionality and option menu
// functionality. In the process of working with textures but there seems to be
// a bug when switching buttons on the main menu that the background texture
// disappears. Currently the health bar for the player decrements in length when 
// taking damage and working on enemy health as well.
#include <iostream>
#include "main.h"
#include "marioH.h"
#include "juliaA.h"
#include "miguelT.h"
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <string>
extern "C" {
#include "fonts.h"
}

using namespace std;

int cursorPos = 0;
Ppmimage *mainbgImage = NULL;
GLuint mainbgTexture;
GLuint mainbgTransTexture;
int mainBg = 1;
bool buttonDisplay = 1;
bool eHealthDisplay = 1;
bool pHudDisplay = 1;


void displayMenu(Game * game)
{
	mainbgImage = ppm6GetImage("menu1.ppm");
	glGenTextures(1, &mainbgTexture);
    
	//background
	glBindTexture(GL_TEXTURE_2D, mainbgTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		mainbgImage->width, mainbgImage->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, mainbgImage->data);

	glBindTexture(GL_TEXTURE_2D, mainbgTexture);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(0, WINDOW_HEIGHT);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(WINDOW_WIDTH, 
				WINDOW_HEIGHT);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(WINDOW_WIDTH, 0);
		glEnd();

	//glClearColor(0.5,0.5,0.5,1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0,60,200);
	declareobject(game,1,150,50,250+5*65,650-5*60);//play button
	declareobject(game,2,150,50,250+5*65,500-5*60);//quit button
	drawobject(game,1);
	drawobject(game,2);
	Rect pButton;
	Rect qButton;
	pButton.bot = 350;
	pButton.left = 520;
	pButton.center = 0;
	if (cursorPos ==0) {
		ggprint16(&pButton, 76, 0x00ffffff, "Play Game");
		
	}
	else
	ggprint16(&pButton, 76, 0x00000000, "Play Game");
	qButton.bot = 200;
	qButton.left = 520;
	qButton.center = 0;
	if (cursorPos ==1) {
		ggprint16(&qButton, 76, 0x00ffffff, "Quit Game");
		
	}
	else
	ggprint16(&qButton, 76, 0x00000000, "Quit Game");
	glColor3ub(200,200,200); //reset to white to keep background image
}

void hudDisplay(Game * game) 
{
	glColor3ub(100,0,0);
bool buttonDisplay = 1;
bool eHealthDisplay = 1;
bool pHudDisplay = 0;

	declareobject(game,game->num_objects+1,game->player.health*15,10,250,860);
	int x =game->map[0], y = game->map[1];
	if (eHealthDisplay == 1) {
		for (int i=0; i < game->current_enemies; i++) {
			declareobject(game,game->num_objects+2,
				game->enemies[x+1][y+1][i].health*2,5,
				game->enemies[x+1][y+1][i].s.center.x,
				game->enemies[x+1][y+1][i].s.center.y+50);
			drawobject(game,game->num_objects+2);
		}
	}
	//if (pHudDisplay == 1) 
		drawobject(game,game->num_objects+1);
	Rect pHealth;
	Rect Weapons;
	Rect wName;
	Rect pKey;
	Rect mKey;
	Rect Key1;
	Rect Key2;
	Rect Key3;
	Rect Key4;
	Rect Key5;
	Rect Key6;
	Rect Key7;

	pHealth.bot = 870; 
	pHealth.left = 210;
	pHealth.center = 0;
	
	Weapons.bot = 870;
	Weapons.left =1010;
	Weapons.center = 0;
	
	wName.bot = 850;
	wName.left = 1010;
	wName.center = 0;
	
	pKey.bot = 830;
	pKey.left = 50;
	pKey.center = 0;

	mKey.bot = 810;
	mKey.left = 50;
	mKey.center = 0;

	Key1.bot = 790;
	Key1.left = 50;
	Key1.center = 0;

	Key2.bot = 770;
	Key2.left = 50;
	Key2.center = 0;

	Key3.bot = 750;
	Key3.left = 50;
	Key3.center = 0;

	Key4.bot = 730;
	Key4.left = 50;
	Key4.center = 0;

	Key5.bot = 710;
	Key5.left = 50;
	Key5.center = 0;

	Key6.bot = 690;
	Key6.left = 50;
	Key6.center = 0;

	Key7.bot = 670;
	Key7.left = 50;
	Key7.center = 0;
	if (pHudDisplay == 1)
		ggprint16(&pHealth, 76, 0x00ffffff, "Health Bar");
	if (buttonDisplay ==1) {
		ggprint08(&pKey,76,0x00ffffff,"p key: Pause Menu");
		ggprint08(&mKey,76,0x00ffffff,"m key: Map Screen");	
		ggprint16(&Weapons,76, 0x00ffffff, "Equiped Weapon");
		ggprint08(&Key1,76, 0x00ffffff, "1 Key: Equip Knife");
		ggprint08(&Key2,76, 0x00ffffff, "2 Key: Equip CrowBar");
		ggprint08(&Key3,76, 0x00ffffff, "3 Key: Equip Shield");
		ggprint08(&Key4,76, 0x00ffffff, "4 Key: Equip Pistol");
		ggprint08(&Key5,76, 0x00ffffff, "5 Key: Equip Shotgun");
		ggprint08(&Key6,76, 0x00ffffff, "6 Key: Equip Rifle");
		ggprint08(&Key7,76, 0x00ffffff, "7 Key: Equip Stun Gun");
	}
	if (game->gun =='1') 
		ggprint16(&wName,76, 0x00ffffff, "Knife");
	if (game->gun == '2')
		ggprint16(&wName,76, 0x00ffffff, "Crowbar");
	if (game->gun == '3')
		ggprint16(&wName,76, 0x00ffffff, "Shield");
	if (game->gun == '4')
		ggprint16(&wName,76, 0x00ffffff, "Pistol");
	if (game->gun == '5')
		ggprint16(&wName,76, 0x00ffffff, "Shotgun");
	if (game->gun == '6')
		ggprint16(&wName,76, 0x00ffffff, "Rifle");
	if (game->gun == '7')
		ggprint16(&wName,76, 0x00ffffff, "Stun Gun");
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
				switch (cursorPos) {
					case 0:
					game->state = 1; //play button case
					initPlayer(game);//initialize players
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
void initPlayer (Game * game)
{
	game->n=0;
	game->num_objects=0;
	game->player.s.width = 20;
	game->player.s.height = 30;
	game->player.s.center.x = 120 + 5*65;
	game->player.s.center.y = 500 - 5*60;
	game->player.velocity.x = 0;
	game->player.velocity.y = 0;
	game->map[0] = 0;
	game->map[1] = 0;
	game->gun = 0;
	game->player.health = Start_HP;
	game->current_enemies = 2;
	game->text_box.center.x = WINDOW_WIDTH/2;
	game->text_box.center.y = 0;
	game->text_box.width = WINDOW_WIDTH/2;
	game->text_box.height = WINDOW_HEIGHT/3;
	game->tutorial = false;
	for (int i = 0; i < 5; i++) {
		game->inv[i] = false;
		game->open[i] = false;
	}
    game->text_count =0;
	if (!game->enemies[game->map[0]+1][game->map[1]+1][0].enemiesInit)
		initEnemies(game, game->map[0], game->map[1]);
		for (int i=0; i < 2; i++) {
			game->enemies[game->map[0]+1][game->map[1]+1][i].health =10;
		}
	

}

void pauseMenuCursor(XEvent *e,Game * game)
{
        if (game->state == 2) {
                if (e->type == KeyPress) {
                        int key = XLookupKeysym(&e->xkey, 0);
                        cout << key << endl;
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
				switch (cursorPos) {
                                        case 0:
                                        game->state = 1; //play button case
                                        break;
					case 1:
					//Check Inventory button case
					//game->state = 6;
					//cursorPos = 0;	
					break;
					case 2:
					//Change Settings button case
					game->state = 6;
					cursorPos = 0;
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

void settingsCursor(XEvent *e,Game * game)
{
        if (game->state == 6) {
                if (e->type == KeyPress) {
                        int key = XLookupKeysym(&e->xkey, 0);
                        cout << key << endl;
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
                                switch (cursorPos) {
                                        case 0:
					if (pHudDisplay == 1)
                                                pHudDisplay = 0;
					else if (pHudDisplay == 0)
                                                pHudDisplay = 1;	
                                        break;
                                        case 1:
					if (eHealthDisplay ==1)
						eHealthDisplay = 0;
					else if (eHealthDisplay == 0)
						eHealthDisplay = 1;
                                        break;
                                        case 2:
					if (buttonDisplay ==1)
						buttonDisplay = 0;
					else if (buttonDisplay == 0)
						buttonDisplay = 1;
					break;
					case 3:
					game->state = 2;
					cursorPos = 0;
                                        break;
                                }
                        }
                }
        }
}


void settingsMenu(Game * game)
{
	cout << pHudDisplay << endl;
	glClearColor(0.5,0.5,0.5,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3ub(100,60,200);
        declareobject(game,5,150,50,200,1100-5*60);
        declareobject(game,6,150,50,200,950-5*60);
        declareobject(game,7,150,50,600,1100-5*60);
        declareobject(game,8,150,50,200,800-5*60);
	declareobject(game,9,150,50,600,950-5*60);
	declareobject(game,10,150,50,200,650-5*60);
	declareobject(game,11,150,50,600,800-5*60);
        drawobject(game,5);
        drawobject(game,6);
        drawobject(game,7);
        drawobject(game,8);
	drawobject(game,9);
	drawobject(game,10);
	drawobject(game,11);

        Rect gButton;
        Rect iButton;
        Rect sButton;
        Rect qButton;
	Rect blButton;
	Rect ehButton;

        gButton.bot = 790;
        gButton.left = 130;
        gButton.center = 0;

	sButton.bot = 790;
	sButton.left = 460;
	sButton.center = 0;
        if (cursorPos ==0) {
                ggprint16(&gButton, 76, 0x00ffffff, "Player Hud Display");
        }
        else
                ggprint16(&gButton, 76, 0x00000000, "Player Hud Display");

        iButton.bot = 640;
        iButton.left = 140;
        iButton.center = 0;
        if (cursorPos == 1) {
                ggprint16(&iButton, 76, 0x00ffffff, "Enemy Health");
        }
	else
                ggprint16(&iButton, 76, 0x00000000, "Enemy Health");
	blButton.bot = 500;
	blButton.left = 140;
	blButton.center = 0;
	if (cursorPos == 2) {
		ggprint16(&blButton, 76, 0x00ffffff, "Button Legend");
	}
	else
		ggprint16(&blButton, 76, 0x00000000, "Button Legend");

        if (pHudDisplay == 1) {
                ggprint16(&sButton, 76, 0x00ffffff, "On");
		pHudDisplay = 1;
        }
	else if (pHudDisplay == 0) {
		ggprint16(&sButton, 76, 0x00ffffff, "Off");
		pHudDisplay = 0;
	}
	
	ehButton.bot = 640;
	ehButton.left = 460;
	ehButton.center = 0;
	blButton.bot = 500;
	blButton.left = 460;
	blButton.center = 0;
	
	if (eHealthDisplay == 1) {
                ggprint16(&ehButton, 76, 0x00ffffff, "On");
		eHealthDisplay = 1;
        }
        else if (eHealthDisplay== 0) {
                ggprint16(&ehButton, 76, 0x00ffffff, "Off");
		eHealthDisplay = 0;
        }

	if (buttonDisplay == 1) {
                ggprint16(&blButton, 76, 0x00ffffff, "On");
		buttonDisplay = 1;
        }
        else if (buttonDisplay == 0) {
                ggprint16(&blButton, 76, 0x00ffffff, "Off");
		buttonDisplay = 0;
        }

        qButton.bot = 340;
        qButton.left = 110;
        qButton.center = 0;
        if (cursorPos == 3) {
                ggprint16(&qButton, 76, 0x00ffffff, "Return to Pause Menu");
        }
        else
        ggprint16(&qButton, 76, 0x00000000, "Return to Pause Menu");
	
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

