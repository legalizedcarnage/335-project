// Miguel Barrales
// 335
// Prison Escape
// Weapon Design/Inventory

#include <iostream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "main.h"
using namespace std;

//initilaze
void knife(Game *game)
{	
	game->knife.k.width = 10;
        game->knife.k.height = 15;
        game->knife.k.center.x = 465; 
        game->knife.k.center.y = 205;
        game->knife.velocity.x = 0;
        game->knife.velocity.y = 0;

}
void pistol(Game *game)
{
	game->pistol.p.width = 10;
        game->pistol.p.height = 20;
        game->pistol.p.center.x = 465;
        game->pistol.p.center.y = 205;
        game->pistol.velocity.x = 0;
        game->pistol.velocity.y = 0;
}
void crowbar(Game *game) {
	game->crowbar.c.width = 10;
        game->crowbar.c.height = 20;
        game->crowbar.c.center.x = 465;
        game->crowbar.c.center.y = 205;
        game->crowbar.velocity.x = 0;
        game->crowbar.velocity.y = 0;
}
void rifle(Game *game)
{
	game->rifle.r.width = 30;
        game->rifle.r.height = 20;
        game->rifle.r.center.x = 465;
        game->rifle.r.center.y = 205;
        game->rifle.velocity.x = 0;
        game->rifle.velocity.y = 0;
}
void shotgun(Game *game)
{
	game->shotgun.sh.width = 30;
        game->shotgun.sh.height = 20;
        game->shotgun.sh.center.x = 465;
        game->shotgun.sh.center.y = 205;
        game->shotgun.velocity.x = 0;
        game->shotgun.velocity.y = 0;
}
void shield(Game *game)
{
	game->shield.s2.width = 30;
        game->shield.s2.height = 40;
        game->shield.s2.center.x = 465;
        game->shield.s2.center.y = 205;
        game->shield.velocity.x = 0;
        game->shield.velocity.y = 0;
}
//makes weapon
void makeKnife(Game *game, int x, int y) {
    if(game->n > Max_Particles)
        return;
    std::cout << "makeParticle() " << x << " " << y << std::endl;
    //position of particle
    Particle *p = &game->particle[game->n];
    p->k.center.x = game->knife.k.center.x;
    p->k.center.y = game->knife.k.center.y;
    p->velocity.y = y;
    p->velocity.x = x;
    game->n++;

}
void makePistol(Game *game, int x, int y) {
    if(game->n > Max_Particles)
        return;
    std::cout << "makeParticle() " << x << " " << y << std::endl;
    //position of particle
    Particle *p = &game->particle[game->n];
    p->p.center.x = game->pistol.p.center.x;
    p->p.center.y = game->pistol.p.center.y;
    p->velocity.y = y;

    p->velocity.x = x;
    game->n++;

}
void makeCrowbar(Game *game, int x, int y) {
    if(game->n > Max_Particles)
        return;
    std::cout << "makeParticle() " << x << " " << y << std::endl;
    //position of particle
    Particle *p = &game->particle[game->n];
    p->c.center.x = game->crowbar.c.center.x;
    p->c.center.y = game->crowbar.c.center.y;
    p->velocity.y = y;
    p->velocity.x = x;
    game->n++;

}
void makeRifle(Game *game, int x, int y) {
    if(game->n > Max_Particles)
        return;
    std::cout << "makeParticle() " << x << " " << y << std::endl;
    //position of particle
    Particle *p = &game->particle[game->n];
    p->r.center.x = game->rifle.r.center.x;
    p->r.center.y = game->rifle.r.center.y;
    p->velocity.y = y;
    p->velocity.x = x;
    game->n++;

}
void makeShotgun(Game *game, int x, int y) {
    if(game->n > Max_Particles)
        return;
    std::cout << "makeParticle() " << x << " " << y << std::endl;
    //position of particle
    Particle *p = &game->particle[game->n];
    p->sh.center.x = game->shotgun.sh.center.x;
    p->sh.center.y = game->shotgun.sh.center.y;   
    p->velocity.y = y;
    p->velocity.x = x;
    game->n++;

}
void makeShield(Game *game, int x, int y) {
    if(game->n > Max_Particles)
        return;
    std::cout << "makeParticle() " << x << " " << y << std::endl;
    //position of particle
    Particle *p = &game->particle[game->n];
    p->s2.center.x = game->shield.s2.center.x;
    p->s2.center.y = game->shield.s2.center.y;
    p->velocity.y = y;
    p->velocity.x = x;
    game->n++;

}
//render weapons
void renderKnife(Game *game)
{
	Shape *k;
	float w,h;
	glColor3ub(255,255,0);
	k = &game->knife.k;
	glPushMatrix();
	glTranslatef(k->center.x, k->center.y, k->center.z);
	w = k->width;
	h = k->height;
	glBegin(GL_QUADS);
	glVertex2i(-w,-h);
	glVertex2i(-w, h);
	glVertex2i( w, h);
	glVertex2i( w,-h);
	glEnd();
	glPopMatrix();	
}
void renderPistol(Game *game)
{
	Shape *p;
        float w,h;
        glColor3ub(255,255,0);
        p = &game->pistol.p;
        glPushMatrix();
        glTranslatef(p->center.x, p->center.y, p->center.z);
        w = p->width;
        h = p->height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w, h);
        glVertex2i( w, h);
        glVertex2i( w,-h);
        glEnd();
        glPopMatrix();
}
void renderCrowbar(Game *game)
{
	Shape *c;
        float w,h;
        glColor3ub(255,255,0);
        c = &game->crowbar.c;
        glPushMatrix();
        glTranslatef(c->center.x, c->center.y, c->center.z);
        w = c->width;
        h = c->height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w, h);
        glVertex2i( w, h);
        glVertex2i( w,-h);
        glEnd();
        glPopMatrix();	
}
void renderRifle(Game *game)
{
	Shape *r;
        float w,h;
        glColor3ub(255,255,0);
        r = &game->rifle.r;
        glPushMatrix();
        glTranslatef(r->center.x, r->center.y, r->center.z);
        w = r->width;
        h = r->height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w, h);
        glVertex2i( w, h);
        glVertex2i( w,-h);
        glEnd();
        glPopMatrix();
}
void renderShield(Game *game)
{
	Shape *s2;
        float w,h;
        glColor3ub(255,255,0);
        s2 = &game->shield.s2;
        glPushMatrix();
        glTranslatef(s2->center.x, s2->center.y, s2->center.z);
        w = s2->width;
        h = s2->height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w, h);
        glVertex2i( w, h);
        glVertex2i( w,-h);
        glEnd();
        glPopMatrix();	
}
void renderShotgun(Game *game)
{
	Shape *sh;
        float w,h;
        glColor3ub(255,255,0);
        sh = &game->shotgun.sh;
        glPushMatrix();
        glTranslatef(sh->center.x, sh->center.y, sh->center.z);
        w = sh->width;
        h = sh->height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w, h);
        glVertex2i( w, h);
        glVertex2i( w,-h);
        glEnd();
        glPopMatrix();
}

