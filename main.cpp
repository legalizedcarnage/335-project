// cs335 group project main
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <unistd.h>
//header files
#include "main.h"
#include "elijahD.h"
#include "marioH.h"
#include "juliaA.h"
#include "miguelT.h"
#include "miguelB.h"
#include "ppm.h"
extern "C" {
#include "fonts.h"
}

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 900

#define MAX_PARTICLES 100
#define GRAVITY 0.1

//backgroung image
Ppmimage *bgImage = NULL;
Ppmimage *bgTransImage = NULL;
GLuint bgTexture;
GLuint bgTransTexture;
int bg = 1;
Ppmimage *playerImage = NULL;
Ppmimage *enemyImage = NULL;
GLuint enemyTexture;
GLuint enemyalphaTexture;
GLuint playerTexture;
GLuint alphaTexture;

//X Windows variables
Display *dpy;
Window win;
GLXContext glc;
//Function prototypes
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_mouse(XEvent *e, Game *game);
int check_keys(XEvent *e, Game *game);
void movement(Game *game);
void charMovement(Game *game);
void render(Game *game);
//void enemiesMovement(Game *game);
//void initEnemies(Game *game);
void physics(Game *game);
int main(void)
{
    int done=0;
    srand(time(NULL));
    initXWindows();
    init_opengl();
    //declare game object
    Game game;
    game.state = 0;
    game.n=0;
    game.num_objects=0;
    game.num_interact=0;
    game.player.s.width = 20;
    game.player.s.height = 30;
    game.player.s.center.x = 120 + 5*65;
    game.player.s.center.y = 500 - 5*60;
    game.player.velocity.x = 0;
    game.player.velocity.y = 0;	
    game.map[0] = 0;
    game.map[1] = 0;
    game.player.health = Start_HP;
    game.current_enemies = 2;
    game.text_box.center.x = 600;
    game.text_box.center.y = 0;
    game.text_box.width = 575;
    game.text_box.height = 275;
    game.tutorial = false; 
    for (int i = 0; i < 5; i++) {
        game.inv[i] = false;
        game.open[i] = false;
    }
    game.text_count =0;
    init_keys(&game);
    initEcount(&game);
    
    //init enemies
    //initEnemies(&game);
    //init enemies
    //knife(&game);
    weapon(&game);
    //start animation
    while (!done) {
	while (XPending(dpy)) {
		XEvent e;
		XNextEvent(dpy, &e);
		check_mouse(&e, &game);
		done = check_keys(&e, &game);
		if (mainMenuCursor(&e, &game) ==1) //main menu
			return 1;
		if (game.state == 2)
			pauseMenuCursor(&e,&game);//pause menu
		if (game.state == 6)
			settingsCursor(&e,&game); //settings
	}
	if (game.state == 1) 
		physics(&game);
	render(&game);
	glXSwapBuffers(dpy, win);
    }
    cleanupXWindows();
    cleanup_fonts();
    return 0;
}

void set_title(void)
{
    //Set the window title bar.
    XMapWindow(dpy, win);
    XStoreName(dpy, win, "335 group project");
}

void cleanupXWindows(void)
{
    //do not change
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}

void initXWindows(void)
{
    //do not change
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    int w=WINDOW_WIDTH, h=WINDOW_HEIGHT;
    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
	std::cout << "\n\tcannot connect to X server\n" << std::endl;
	exit(EXIT_FAILURE);
    }
    Window root = DefaultRootWindow(dpy);
    XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
    if (vi == NULL) {
	std::cout << "\n\tno appropriate visual found\n" << std::endl;
	exit(EXIT_FAILURE);
    } 
    Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
	ButtonPress | ButtonReleaseMask |
	PointerMotionMask |
	StructureNotifyMask | SubstructureNotifyMask;
    win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
	InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    set_title();
    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);
}

unsigned char *buildAlphaData(Ppmimage *img)
{
	//add 4th component to RGB stream...
	int i;
	int a,b,c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	for (i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		//get largest color component...
		//*(ptr+3) = (unsigned char)((
		//		(int)*(ptr+0) +
		//		(int)*(ptr+1) +
		//		(int)*(ptr+2)) / 3);
		//d = a;
		//if (b >= a && b >= c) d = b;
		//if (c >= a && c >= b) d = c;
		//*(ptr+3) = d;
		*(ptr+3) = (a|b|c);
		ptr += 4;
		data += 3;
	}
	return newdata;
}
void init_opengl(void)
{
    //OpenGL initialization
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //Set 2D mode (no perspective)
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    //Set the screen background color
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();

    //background image
    bgImage = ppm6GetImage("bg.ppm");

    glGenTextures(1, &bgTexture);
    
    //background
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
		bgImage->width, bgImage->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, bgImage->data);

    //player image
    playerImage = ppm6GetImage("player.ppm");
    glGenTextures(1, &playerTexture);
    glBindTexture(GL_TEXTURE_2D, playerTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
		playerImage->width, playerImage->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, playerImage->data);
 
    //player alpha
    glGenTextures(1, &alphaTexture);
    unsigned char *alphaData = buildAlphaData(playerImage);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,playerImage->width,
	    playerImage->height,0, GL_RGBA,GL_UNSIGNED_BYTE,alphaData);
    free(alphaData);

    //enemy image
    enemyImage = ppm6GetImage("enemy.ppm");
    glGenTextures(1, &enemyTexture);
    glBindTexture(GL_TEXTURE_2D, enemyTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
		enemyImage->width, enemyImage->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, enemyImage->data);
    //enemy alpha
    glGenTextures(1, &enemyalphaTexture);
    unsigned char *enemyalphaData = buildAlphaData(enemyImage);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,enemyImage->width,
	    enemyImage->height,0, GL_RGBA,GL_UNSIGNED_BYTE,enemyalphaData);
    free(enemyalphaData);

    //background transparent part
/*    glBindTexture(GL_TEXTURE_2D, bgTransTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //must build a new set of data...
    //int w = bgTransImage->width;
	int h = bgTransImage->height;
	unsigned char *ftData = buildAlphaData(bgTransImage);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, ftData);
	free(ftData);
*/
}
void check_mouse(XEvent *e, Game *game)
{
    static int savex = 0;
    static int savey = 0;
    static int n = 0;

    if (e->type == ButtonRelease) {
	return;
    }
    if (e->type == ButtonPress) {
	if (e->xbutton.button==1) {
		//Left button was pressed
		//int y = WINDOW_HEIGHT - e->xbutton.y - game->player.s.center.y;
		//int x = e->xbutton.x - game->player.s.center.x;
		//makeParticle(game, x, y);
		return;
	}
	if (e->xbutton.button==3) {
		//Right button was pressed
		return;
	}
    }
    //Did the mouse move?
    if (savex != e->xbutton.x || savey != e->xbutton.y) {
	savex = e->xbutton.x;
	savey = e->xbutton.y;
	if (++n < 10)
		return;
    }
}

int check_keys(XEvent *e, Game *game)
{
    //Was there input from the keyboard?
    if (e->type == KeyPress) {
	int key = XLookupKeysym(&e->xkey, 0);
	if (key == XK_Escape) {
		return 1;
	}

	switch (key) {
		case XK_b:
			bg ^=1;
			break;
		case XK_Left:
		//may need to adjust
		
		game->player.velocity.x = -5;
		game->direction = 'l';
		break;
		case XK_Right:
		game->player.velocity.x = 5;
		game->direction = 'r';

		break;
		case XK_Up:
		game->player.velocity.y = 5;
		game->direction = 'u';
		break;
		case XK_Down:
		game->player.velocity.y = -5;
		game->direction = 'd';
		break;
		case XK_1:
		game->gun = '1';
		break;
		case XK_2:
		game->gun = '2';
		break;
		case XK_3:
		game->gun = '3';
		break;
		case XK_4:
		game->gun = '4';
		break;
		case XK_5:
		game->gun = '5';
		break;
		case XK_6:
		game->gun = '6';
		break;
		case XK_7:
		game->gun = '7';
		break;
		case XK_space:
		if (game->state == 4) {
			if (game->text_count == 2) {
				game->state = 1;
				game->text_count = 0;
			}
			else 
				game->text_count++;
		}		
		game->space = 's';
		switch (game->direction) {
			case 'l':
			if (game->gun > 3) {
			makeParticle(game, -8, 0);
			}
			break;
			case 'r':
			if (game->gun > 3) {
			makeParticle(game, 8, 0);
			}
			break;
			case 'u':
			if (game->gun > 3) {
			makeParticle(game, 0, 8);
			}
			break;
			case 'd':
			if (game->gun > 3) {
			makeParticle(game, 0, -8);
			}
			break;
		}
		break;
		
		case XK_p:
		std::cout << "p button pressed" << std::endl;
		if (game->state==1) {
			game->state=2;
			break;
		}
		else if (game->state==2) {
			game->state=1;
			break;
		}
		break;
		case XK_m:
		if (game->state == 1) {
			game->state = 3;
			break;
		} else if (game->state == 3) {
			game->state = 1;
			break;
		}
		break;
		case 92:
		game->tutorial = true;
		break;
        case XK_h:
            hard();
            std::cout << "Hardmode\n";
        break;		
	}
    }
    if ( e->type == KeyRelease) {
	int key = XLookupKeysym(&e->xkey, 0);
	switch (key) {
		case XK_Left:
		if (game->player.velocity.x < 0)	
			game->player.velocity.x = 0;
		break;
		case XK_Right:
		if (game->player.velocity.x > 0)	
			game->player.velocity.x = 0;
		break;
		case XK_Up:
		if (game->player.velocity.y > 0)	
			game->player.velocity.y = 0;
		break;
		case XK_Down:
		if (game->player.velocity.y < 0)	
			game->player.velocity.y = 0;
		break;
	}

    }
    return 0;
}
void physics(Game *game) 
{
	charMovement(game);
	//enemiesMovement(game);
	movement(game);
}
void charMovement( Game *game) 
{
    Player *p;
    p = &game->player;
    particleCollision(game);
    playerCollision(game);
    interact(game);
    p->s.center.x += p->velocity.x;
    p->s.center.y += p->velocity.y;
    weaponMov(game);
}

void render(Game *game)
{
    if (game->state == 0) {
	displayMenu(game);
    }
    else if (game->state ==1) {
	glClearColor(0.0,0.0,0.0,1.0);
	float w, h;
	glClear(GL_COLOR_BUFFER_BIT);
	if (bg) {
		glBindTexture(GL_TEXTURE_2D, bgTexture);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(0, WINDOW_HEIGHT);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(WINDOW_WIDTH, 0);
		glEnd();
        }
	//Layout of the game
	doors(game);
	printtile(game);
	//draw current tile
	Shape *s;
	for (int i = 0; i < game->num_objects; i++ ) {
		glColor3ub(90,140,90);
		s = &game->box;
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
	//draw all particles here
	renderParticles(game);
	//draw keys

	Print_keys(game);
	//draw player	
	renderWeapon(game);
	glColor4f(1.0f,1.0f,1.0f,0.8f);
	s = &game->player.s;
	w = s->width;
	h = s->height;
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.0f);
	glBindTexture(GL_TEXTURE_2D, playerTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); 
		if (game->direction == 'd')
			glVertex2i(s->center.x-w,s->center.y-h);
		else if (game->direction == 'u')
			glVertex2i(s->center.x+w,s->center.y+h);
		else if (game->direction == 'l')
			glVertex2i(s->center.x-w,s->center.y+h);
		else 
			glVertex2i(s->center.x+w,s->center.y-h);
		glTexCoord2f(0.0f, 0.0f); 
		if (game->direction == 'd')
			glVertex2i(s->center.x-w,s->center.y+h);
		else if (game->direction == 'u')
			glVertex2i(s->center.x+w,s->center.y-h);
		else if (game->direction == 'l')
			glVertex2i(s->center.x+w,s->center.y+h);
		else 
			glVertex2i(s->center.x-w,s->center.y-h);
		glTexCoord2f(1.0f, 0.0f); 
		if (game->direction == 'd')
			glVertex2i(s->center.x+w,s->center.y+h);
		else if (game->direction == 'u')
			glVertex2i(s->center.x-w,s->center.y-h);
		else if (game->direction == 'l')
			glVertex2i(s->center.x+w,s->center.y-h);
		else 
			glVertex2i(s->center.x-w,s->center.y+h);
		glTexCoord2f(1.0f, 1.0f); 
		if (game->direction == 'd')
			glVertex2i(s->center.x+w,s->center.y-h);
		else if (game->direction == 'u')
			glVertex2i(s->center.x-w,s->center.y+h);
		else if (game->direction == 'l')
			glVertex2i(s->center.x-w,s->center.y-h);
		else 
			glVertex2i(s->center.x+w,s->center.y+h);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST);
	//print player 
	//glPushMatrix();
	//glTranslatef(s->center.x, s->center.y, s->center.z);
	//w = s->width;
	//h = s->height;
	//glBegin(GL_QUADS);
	//glVertex2i(-w,-h);
	//glVertex2i(-w, h);
	//glVertex2i( w, h);
	//glVertex2i( w,-h);
	//glEnd();
	//glPopMatrix();
	
	glColor3ub(0,0,0);
	
	renderEnemies(game, game->map[0], game->map[1]);
	hudDisplay(game);
	if (game->tutorial == true) {
		game->state = 4;
		game->tutorial = false;
	}
    }
    else if (game->state==2)
	pauseMenu(game);
    else if (game->state == 3)
	map(game);
    else if (game->state == 4) {
	text(game);
    }
    else if (game->state == 5) {
	usleep(3000000);
	game->state = 0;
    }
    else if (game->state == 6)
    		settingsMenu(game);
}


