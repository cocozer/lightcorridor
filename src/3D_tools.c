#include "3D_tools.h"

/* Camera parameters and functions */
float theta = 90.0f; // Angle between x axis and viewpoint
float phy = 90.0f; // Angle between z axis and viewpoint
float dist_zoom = 1.0f; // Distance between origin and viewpoint

void setCamera() {
	gluLookAt(0, 0, 0, // Caméra placée en 0 0 0
			  0.0,1.0,0.0, // Regarde vers l'axe Y positif
			  0.0,0.0,1.0); // Le haut de la caméra est l'axe Z positif
}

/* Convert degree to radians */
float toRad(float deg) {
	return deg*M_PI/180.0f;
}


void drawSquare() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-0.25,1,-0.25);
		glVertex3f(-0.25,1,0.25);
		glVertex3f(0.25,1,0.25);
		glVertex3f(0.25,1,-0.25);
	glEnd();
}

void drawCircle() {
	glPushMatrix(); // Sauvegarde de la matrice
        glScalef(0.1, 0.1, 0.1); // Déplacement du plan
    
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0.0,0.0,0.0);
			float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
			for(int i=0;i<=NB_SEG_CIRCLE;i++) {
				glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
			}
		glEnd();
	glPopMatrix(); // Reload de la matrice sauvegardée
}

void drawCone() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,1.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawSphere() {
	gluSphere(gluNewQuadric(),1,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
}

void drawRaquette() {
	glBegin(GL_LINE);
		glVertex3f(-0.25,0,-0.25);
		glVertex3f(-0.25,0,0.25);
		glVertex3f(0.25,0,0.25);
		glVertex3f(0.25,0,-0.25);
	glEnd();
}

void drawBorderCorridor() {
	glBegin(GL_LINE_LOOP);
		glVertex3f(-0.5,0,0.25);
		glVertex3f(0.5,0,0.25);
		glVertex3f(0.5,0,-0.25);
		glVertex3f(-0.5,0,-0.25);
	glEnd();
	
}


void drawWall(){ //dessine un mur entier

    glBegin(GL_QUADS);
		glVertex3f(-5,30,-2.5);
		glVertex3f(-5,30,2.5);
		glVertex3f(5,30,2.5);
		glVertex3f(5,30,-2.5);
	glEnd();
}

void drawUpsideWall(){ //dessine le mur du haut

    glBegin(GL_QUADS);
		glVertex3f(-5,30,-2.5);
		glVertex3f(-5,30,0);
		glVertex3f(5,30,0);
		glVertex3f(5,30,-2.5);
	glEnd();
}

void drawRightWall(){
	glBegin(GL_QUADS);
		glVertex3f(0,30,-2.5);
		glVertex3f(0,30,2.5);
		glVertex3f(5,30,2.5);
		glVertex3f(5,30,-2.5);
	glEnd();


}

