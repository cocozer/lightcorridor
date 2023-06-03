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
	// glBegin(GL_TRIANGLE_FAN);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-0.1,0,-0.1);
		glVertex3f(-0.1,0,0.1);
		glVertex3f(0.1,0,0.1);
		glVertex3f(0.1,0,-0.1);
	glEnd();
}

void drawFilledSquare() {
    glBegin(GL_QUADS);
    glVertex3f(-0.1, 0, -0.1);
    glVertex3f(-0.1, 0, 0.1);
    glVertex3f(0.1, 0, 0.1);
    glVertex3f(0.1, 0, -0.1);
    glEnd();
}

void drawScaledSquare(float scale) {
    glPushMatrix(); // Sauvegarde de la matrice
    glScalef(scale, scale, scale); // Scaling
    drawSquare();
    glPopMatrix(); // Reload de la matrice sauvegardée
}


void drawCube() {
	glBegin(GL_LINE_LOOP);
		drawSquare();
		glPushMatrix(); // Sauvegarde de la matrice
		glTranslatef(0., 0.2f, 0.); // Déplacement du plan
			drawSquare();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 0., 0., 1.); // rotation
			glTranslatef(0.1f, 0.1f, 0.); // Déplacement du plan
			drawSquare();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 0., 0., 1.); // rotation
			glTranslatef(0.1f, -0.1f, 0.); // Déplacement du plan
			drawSquare();
		glPopMatrix();
	glEnd();
}

void drawFilledCube() {
	drawFilledSquare();
		glPushMatrix(); // Sauvegarde de la matrice
		glTranslatef(0., 0.2f, 0.); // Déplacement du plan
			drawFilledSquare();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 0., 0., 1.); // rotation
			glTranslatef(0.1f, 0.1f, 0.); // Déplacement du plan
			drawFilledSquare();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 0., 0., 1.); // rotation
			glTranslatef(0.1f, -0.1f, 0.); // Déplacement du plan
			drawFilledSquare();
		glPopMatrix();

}

void updateRotationAngle(){
	rotationAngle += 1.0; // Augmenter l'angle de rotation
    if (rotationAngle >= 360.0) {
        rotationAngle =0; // Remise à zéro de l'angle
    }
}

void drawRotatedCube() {
	glColor3f(255,0,0);
	glBegin(GL_LINE_LOOP);
		glPushMatrix();
			//glRotatef(rotationAngle, 0, 0, 1);
			drawSquare();
			glPushMatrix(); // Sauvegarde de la matrice
			glTranslatef(0., 0.2f, 0.); // Déplacement du plan
				glRotatef(rotationAngle, 0, 1, 0);
				drawSquare();
			glPopMatrix();
			glPushMatrix();
				glRotatef(90, 0., 0., 1.); // rotation
				glTranslatef(0.1f, 0.1f, 0.); // Déplacement du plan
				glRotatef(rotationAngle, 0, 0, 1);
				drawSquare();
			glPopMatrix();
			glPushMatrix();
				glRotatef(90, 0., 0., 1.); // rotation
				glTranslatef(0.1f, -0.1f, 0.); // Déplacement du plan
				glRotatef(rotationAngle, 0, 0, 1.);
				drawSquare();
			glPopMatrix();
		glPopMatrix();
	glEnd();
}

void drawScaledCube(float scale, float rotate, float full){
	glPushMatrix(); // Sauvegarde de la matrice
    glScalef(scale, scale, scale); // Scaling
	if (rotate ==1){
		glRotatef(rotationAngle,0,0,1);
	}
	if (full == 0){
		drawCube();
	} else {
		drawFilledCube();
	}
    
    glPopMatrix(); // Reload de la matrice sauvegardée
}

void drawCircle() {
	glPushMatrix(); // Sauvegarde de la matrice
        glScalef(0.05, 0.05, 0.05); // Resize du plan
    
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0.0,0.0,0.0);
			float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
			for(int i=0;i<=NB_SEG_CIRCLE;i++) {
				glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
			}
		glEnd();
	glPopMatrix(); // Reload de la matrice sauvegardée
}

void drawHeartCube(){
	glColor3f(255,0,0);
	glPushMatrix();
		glPushMatrix();
			glTranslatef(-0.002,0,0.002);
			glRotatef(40,0,1,0);
			drawScaledCube(0.1,0,1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.04,0,0);
			glRotatef(40,0,1,0);
			drawScaledCube(0.1,0,1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.02,0,-0.015);
			glRotatef(40,0,1,0);
			drawScaledCube(0.13,0,1);
		glPopMatrix();
	glPopMatrix();
}

void drawArrow(){
	glColor3f(0,255,0); //vert
	glPushMatrix();
		glPushMatrix();
			glTranslatef(-0.01,0,0.002);
			glRotatef(40,0,1,0);
			glScalef(2,0,0.7);
			drawScaledCube(0.1,0,1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.03,0,0);
			glRotatef(135,0,1,0);
			glScalef(2,0,0.7);
			drawScaledCube(0.1,0,1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.02,0,-0.01);
			glRotatef(90,0,1,0);
			glScalef(2,0,0.7);
			drawScaledCube(0.1,0,1);
		glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0,0,0); // foncé
		glTranslatef(0,0.02,0);
		glScalef(1.1,1.1,1.1);
		glPushMatrix();
			glTranslatef(-0.01,0,0.002);
			glRotatef(40,0,1,0);
			glScalef(2,0,0.7);
			drawScaledCube(0.1,0,1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.03,0,0);
			glRotatef(135,0,1,0);
			glScalef(2,0,0.7);
			drawScaledCube(0.1,0,1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.02,0,-0.01);
			glRotatef(90,0,1,0);
			glScalef(2,0,0.7);
			drawScaledCube(0.1,0,1);
		glPopMatrix();

	glPopMatrix();
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
	gluSphere(gluNewQuadric(),0.5,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
}

void drawTexturedSphere(float radius, int stacks, int slices) {
    float stackStep = M_PI / stacks;
    float sliceStep = 2.0f * M_PI / slices;

    for (int i = 0; i < stacks; i++) {
        float theta1 = i * stackStep;
        float theta2 = (i + 1) * stackStep;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float phi = j * sliceStep;

            // Vertex 1
            float x1 = radius* sin(theta1) * cos(phi);
            float y1 = radius * cos(theta1);
            float z1 = radius * sin(theta1) * sin(phi);
            glTexCoord2f((float)j / slices, (float)i / stacks);
            glVertex3f(x1, y1, z1);

            // Vertex 2
            float x2 = radius * sin(theta2) * cos(phi);
            float y2 = radius * cos(theta2);
            float z2 = radius * sin(theta2) * sin(phi);
            glTexCoord2f((float)j / slices, (float)(i + 1) / stacks);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
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
		glVertex3f(-5,0,-2.5);
		glVertex3f(-5,0,2.5);
		glVertex3f(5,0,2.5);
		glVertex3f(5,0,-2.5);
	glEnd();
}

void drawUpsideWall(){ //dessine le mur du haut

    glBegin(GL_QUADS);
		glVertex3f(-0.5,0,0.25);
		glVertex3f(0.5,0,0.25);
		glVertex3f(0.5,0,0);
		glVertex3f(-0.5,0,0);
	glEnd();
}

void drawRightWall(){
	glBegin(GL_QUADS);
		glVertex3f(0,0,-0.25);
		glVertex3f(0,0,0.25);
		glVertex3f(0.5,0,0.25);
		glVertex3f(0.5,0,-0.25);
	glEnd();


}

void drawRectangle() {
	glBegin(GL_QUADS);
		glVertex3f(-0.5,0,-0.1);
		glVertex3f(-0.5,0,0.1);
		glVertex3f(0.5,0,0.1);
		glVertex3f(0.5,0,-0.1);
	glEnd();
}

void drawTexturedRectangle() {
	glBegin(GL_QUADS);
            glTexCoord2f(0,0);
            glVertex3f(-0.5,0,0.1);
            glTexCoord2f(1,0);
            glVertex3f(0.5,0,0.1);
            glTexCoord2f(1,1);
            glVertex3f(0.5,0,-0.1);
            glTexCoord2f(0,1);
            glVertex3f(-0.5,0,-0.1);
    glEnd();
}

void drawTexturedSquare(){
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(-0.1,0,-0.1);
		glTexCoord2f(0,0);
		glVertex3f(-0.1,0,0.1);
		glTexCoord2f(1,0);
		glVertex3f(0.1,0,0.1);
		 glTexCoord2f(1,1);
		glVertex3f(0.1,0,-0.1);
	glEnd();

}