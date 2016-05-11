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

//header files
#include "main.h"
#include "elijahD.h"
#include "marioH.h"
#include "juliaA.h"
#include "miguelT.h"
#include "miguelB.h"
extern "C" {
#include "fonts.h"
}

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 900

#define MAX_PARTICLES 100
#define GRAVITY 0.1

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
void initEnemies(Game *game);
void physics(Game *game);
//global variable
//int click = 0;
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
    game.player.s.width = 20;
    game.player.s.height = 30;
    game.player.s.center.x = 120 + 5*65;
    game.player.s.center.y = 500 - 5*60;
    game.player.velocity.x = 0;
    game.player.velocity.y = 0;	
    game.map[0] = 0;
    game.map[1] = 0;
    //init enemies
    initEnemies(&game);
    //init enemies
    weapon(&game);
    //start animation
    while(!done) {
	while(XPending(dpy)) {
		XEvent e;
		XNextEvent(dpy, &e);
		check_mouse(&e, &game);
		done = check_keys(&e, &game);
		if (mainMenuCursor(&e, &game) ==1) //main menu
			return 1;
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

}

void makeParticle(Game *game, int x, int y) 
{
    if (game->n > Max_Particles)
	return;	    
    std::cout << "makeParticle() " << x << " " << y << std::endl;
    //position of particle
    Particle *p = &game->particle[game->n];
    if(game->gun == '1') {
    p->s.center.x = game->object[91].center.x;
    p->s.center.y = game->object[91].center.y;
    }if(game->gun == '2') {
    p->s.center.x = game->object[92].center.x;
    p->s.center.y = game->object[92].center.y;
    }if(game->gun == '3') {
    p->s.center.x = game->object[93].center.x;
    p->s.center.y = game->object[93].center.y;
    }if(game->gun == '4') {
    p->s.center.x = game->object[94].center.x;
    p->s.center.y = game->object[94].center.y;
    }if(game->gun == '5') {
    p->s.center.x = game->object[95].center.x;
    p->s.center.y = game->object[95].center.y;
    }if(game->gun == '6') {
    p->s.center.x = game->object[96].center.x;
    p->s.center.y = game->object[96].center.y;
    }if(game->gun == '7') {
    p->s.center.x = game->object[97].center.x;
    p->s.center.y = game->object[97].center.y;
    }
    //double z = sqrt(x*x + y*y);
    p->velocity.y = y;
    p->velocity.x = x;
    game->n++;

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

	switch(key) {
		case XK_Left:
		//may need to adjust
		game->player.velocity.x -= 5;
		game->direction = 'l';
		break;
		case XK_Right:
		game->player.velocity.x += 5;
		game->direction = 'r';

		break;
		case XK_Up:
		game->player.velocity.y += 5;
		game->direction = 'u';
		break;
		case XK_Down:
		game->player.velocity.y -= 5;
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
		switch(game->direction) {
			case 'l':
			makeParticle(game, -8, 0);
			break;
			case 'r':
			makeParticle(game, 8, 0);
			break;
			case 'u':
			makeParticle(game, 0, 8);
			break;
			case 'd':
			makeParticle(game, 0, -8);
			break;
		}
		break;
	}
    }
    if ( e->type == KeyRelease) {
	int key = XLookupKeysym(&e->xkey, 0);
	switch(key) {
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
void movement(Game *game)
{
    Particle *p;

    if (game->n <= 0)
	return;
    for (int i = 0; i < game->n; i++) {
	p = &game->particle[i];
	p->s.center.x += p->velocity.x;
	p->s.center.y += p->velocity.y;

    }
}
void charMovement( Game *game) 
{
    Player *p;
    p = &game->player;
    particleCollision(game);
    playerCollision(game);
     
    p->s.center.x += p->velocity.x;
    p->s.center.y += p->velocity.y;

    weaponMov(game);
}
void render(Game *game)
{
    //game->state = 0;
    if (game->state == 0)
	displayMenu(game);
    else {
	glClearColor(0.0,0.0,0.0,1.0);
	float w, h;
	glClear(GL_COLOR_BUFFER_BIT);
	//Layout of the game
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
	for (int i = 0; i < game->n; i++) {
		glPushMatrix();
		glColor3ub(150,160,220);
		Vec *c = &game->particle[i].s.center;
		w = 2;
		h = 2;
		glBegin(GL_QUADS);
		glVertex2i(c->x-w, c->y-h);
		glVertex2i(c->x-w, c->y+h);
		glVertex2i(c->x+w, c->y+h);
		glVertex2i(c->x+w, c->y-h);
		glEnd();
		glPopMatrix();
	}
	//draw player	
	glColor3ub(150,160,220);
	s = &game->player.s;
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
	/*
	//draw enemies	
	glColor3ub(250,50,50);
	s = &game->enemies[0].s;
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
	*/
	//renders enemies
	renderWeapon(game);
	//renderEnemies(game);
	hudDisplay(game);
    }
}


