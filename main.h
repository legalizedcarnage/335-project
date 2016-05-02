//struct header file
#ifndef MAIN_H
#define MAIN_H

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 900
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
	Shape p;
	Shape k;
	Shape c;
	Shape r;
	Shape s2;
	Shape sh;
	Vec velocity;
};

struct Player {
    	Shape s;
    	int health;
	Vec velocity;
};
struct Pistol {
	Shape p;
	Vec velocity;
};
struct Shield {	
	Shape s2;
	Vec velocity;
};
struct Shotgun {
	Shape sh;
	Vec velocity;
};
struct Knife {
	Shape k;
	Vec velocity;
};
struct Crowbar {
	Shape c;
	Vec velocity;
};
struct Rifle {
	Shape r;
	Vec velocity;
};
struct Game {
	int state;
    	char direction;
        int map[2];
	Player enemies[Max_Enemies] ;
	Player player;
	Shape button1; //play
	Shape button2; //quit
	Shape object[Max_Objects];
	//weapons
	Shield shield;
	Shotgun shotgun;
	Knife knife;
	Crowbar crowbar;
	Rifle rifle;
	Pistol pistol;
	//wepaons
	Particle particle[Max_Particles];
	Shape box;
	int n;
	int num_objects;

};


#endif
