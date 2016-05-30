//struct header file
#ifndef MAIN_H
#define MAIN_H
#include "ppm.h"
#include <GL/glx.h>
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 900
const unsigned int Max_Enemies = 10;
const int Max_Objects = 100;
const int Max_Particles = 100;
const int Start_HP = 10;
extern GLuint enemyTexture;

struct Vec {
	float x, y, z;
};

struct Shape {
	float width, height;
	float radius;
	Vec center;

	//Vec velocity;
};

struct Particle {
	Shape s;
	Shape r;
	Shape t;
	Vec velocity;
	Vec velocity2;
	Vec velocity3;
};

struct Player {
    	Shape s;
    	int health;
	Vec velocity;
	bool enemiesInit;
};
struct Game {
	int state;
    	char direction;
	char gun;
	char space;
	bool mele;
        int map[2];
	Player enemies[100][100][10] ;
	Player player;
	Shape button1; //play
	Shape button2; //quit
	Shape object[Max_Objects];
	Particle particle[Max_Particles];
	Shape box;
	int n;
	int num_objects;
	int num_enemies;
	int current_enemies;
	Shape keys[5];
	bool inv[5];
	bool open[5];
	int key_num;
	int num_interact;
	Shape interact[5];
	Shape text_box;
	bool tutorial;
	int text_count;
};
unsigned char *buildAlphaData(Ppmimage *img);
#endif
