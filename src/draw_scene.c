#include "draw_scene.h"
#include "3D_tools.h"
float red = 0;
float green = 0;
float blue = 0;
void drawDecor() {
    // Couleur
    red = 169.0/255; // Rouge
    green = 234.0/255; // Vert
    blue = 254.0/255; // Bleu
    glColor3f(red, green, blue);

    // Rectangle bas
    glBegin(GL_QUADS);
		glVertex3f(-0.5,0,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(0.5,0,-0.5);
	glEnd();
    
    // Rectangle haut
    glBegin(GL_QUADS);
		glVertex3f(-0.5,0,0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0,0.5);
	glEnd();

    // Couleur
    red = 116.0/255; // Rouge
    green = 208.0/255; // Vert
    blue = 241.0/255; // Bleu
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
		glVertex3f(-0.5,0,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,0,0.5);
	glEnd();
    glBegin(GL_QUADS);
		glVertex3f(0.5,0,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0,0.5);
    glEnd();
}