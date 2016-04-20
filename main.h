//main header file
#ifndef MAIN_H
#define MAIN_H
const unsigned int Max_Enemies = 10;
const int Max_Objects = 100;
const int Max_Particles = 100;
struct Vec {
	float x, y, z;
};

struct Shape {
	float width, height;
	float radius;
	Vec center;
};

struct Particle {
	Shape s;
	Vec velocity;
};

struct Player {
    	Shape s;
	Vec velocity;
};

struct Game {
	int state;
    	char direction;
	Player enemies[Max_Enemies] ;
	Player player;
	Shape object[Max_Objects];
	Particle particle[Max_Particles];
	Shape box;
	int n;
};

//Function prototypes
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_mouse(XEvent *e, Game *game);
int check_keys(XEvent *e, Game *game);
void movement(Game *game);
void charMovement(Game *game);
void render(Game *game);


#endif
