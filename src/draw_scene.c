#include "draw_scene.h"
#include "3D_tools.h"

void drawDecor() {
    glBegin(GL_QUADS);
		glVertex3f(-0.5,0,-0.5);
		glVertex3f(-0.5,0.2,-0.5);
		glVertex3f(0.5,0.2,-0.5);
		glVertex3f(0.5,0,-0.5);
	glEnd();
}