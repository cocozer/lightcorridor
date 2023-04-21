#define GLFW_INCLUDE_NONE
#if defined(__APPLE__)
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "TD03 Ex01";
static float aspectRatio = 1.0;

int alpha = 45;
int beta = -10;
int gam = 35;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 20.;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if( aspectRatio > 1)
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}
	glMatrixMode(GL_MODELVIEW);

}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE); 
				break;
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			default: fprintf(stdout,"Touche non gérée\n");
		}
	}
}

void drawOrigin(){
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2f(-0.5, 0);
		glVertex2f(0.5, 0);
		glColor3f(0, 1, 0);
		glVertex2f(0, -0.5);
		glVertex2f(0, 0.5);
  	glEnd();
}
void drawSquare(){
	glBegin(GL_QUADS);
		glColor3f(1, 0.4, 0.8);
		glVertex2f(-0.5, 0.5); // vertex 1
		glVertex2f(0.5, 0.5); // vertex 2
		glVertex2f(0.5, -0.5); // vertex 3
		glVertex2f(-0.5, -0.5); // vertex 4
	glEnd();

}
void drawCircle(int pts) {

    double rayon = 1.0;
  
    glBegin(GL_POLYGON);

    for (int i = 0; i < pts; i++) {
        glVertex2f( rayon*cos(i*(2*M_PI/pts)) , rayon*sin(i*(2*M_PI/pts)));
    }
    //cout << "cos: "<< cos(M_PI/2) << "sin: "<< sin(M_PI/2) ;
    glEnd();


}

void drawMainArm(){
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex2f(0, 2);
		glVertex2f(6, 1); 
		glVertex2f(6, -1);
		glVertex2f(0, -2);
	glEnd();

	glColor3f(0,1,0);

	//premier cercle (le grand)

    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(-0.5, 0., 0.); // Déplacement du plan
        glScalef(2, 2, 2); // Resize du plan
        drawCircle(50); // Dessin du cercle déplacé
    glPopMatrix(); // Reload de la matrice sauvegardée

	//deuxième cercle
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(6, 0., 0.); // Déplacement du plan
        glScalef(1, 1, 1); // Resize du plan
        drawCircle(50); // Dessin du cercle déplacé
    glPopMatrix(); // Reload de la matrice sauvegardée

	// //lignes
    // glBegin(GL_LINES);
	// 	glColor3f(1., 1., 1.);
	// 	glVertex2f(0, 2);
	// 	glVertex2f(6, 1); 
    // glEnd();

    // glBegin(GL_LINES);
	// 	glColor3f(1., 1., 1.);
	// 	glVertex2f(0, -2);
	// 	glVertex2f(6, -1);
    // glEnd();

}

void drawRoundedSquare(){
	glColor3f(1., 1., 1.);

	//carré
	glPushMatrix();
		glTranslatef(-0.5, 0., 0.); // Déplacement du plan
		glScalef(1,1,1);
		drawSquare();
	glPopMatrix;

	//rond1

	// glColor3f(1., 0, 1.);
	// glPushMatrix();
	// 	glTranslatef(0.42, 0.42, 0.); // Déplacement du plan
	// 	glScalef(0.1,0.1,0.1);
	// 	drawCircle(100);
	// glPopMatrix;

	// glPushMatrix();
	// 	glTranslatef(-1.5, 0.5, 0.); // Déplacement du plan
	// 	glScalef(5,5,5);
	// 	drawCircle(50);
	// glPopMatrix;

	// glPushMatrix();
	// 	glTranslatef(-0.42, -0.42, 0.); // Déplacement du plan
	// 	glScalef(0.1,0.1,0.1);
	// 	drawCircle(50);
	// glPopMatrix;

	// glPushMatrix();
	// 	glTranslatef(0.42, -0.42, 0.); // Déplacement du plan
	// 	glScalef(0.1,0.1,0.1);
	// 	drawCircle(50);
	// glPopMatrix;

}

void drawSecondArm(){
	glPushMatrix();
    glTranslatef(0.45, 0., 0.);
       drawRoundedSquare();
        glPushMatrix(); // Sauvegarde de la matrice
            glTranslatef(4.5, 0., 0.); // Déplacement du plan
            drawRoundedSquare(); // Dessin du cercle déplacé
        glPopMatrix(); // Reload de la matrice sauvegardée
	glPopMatrix;
	glPushMatrix();
		glTranslatef(-0.4, 0, 0);
			glBegin(GL_QUADS);
				glColor3f(5, 5, 5);
				glVertex2f(0, -0.3);
				glVertex2f(0, 0.3);
				glVertex2f(4.6, 0.3);
				glVertex2f(4.6, -0.3);
			glEnd();
    glPopMatrix();
}

void drawDrummer() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glBegin(GL_QUADS);
        glColor3f(1., 1., 1.);
        glVertex2f(3.6, 0.15);
        glVertex2f(3.6, -0.15);
        glVertex2f(0, -0.15);
        glVertex2f(0, 0.15);
    glEnd();

    glColor3f(0.3, 0.3, 0.3);

		glPushMatrix(); // Sauvegarde de la matrice
            glScalef(0.4, 0.4, 0.4); // Resize du plan
            drawSquare(); // Dessin du cercle déplacé
        glPopMatrix(); // Reload de la matrice sauvegardée


        glPushMatrix(); // Sauvegarde de la matrice
            glTranslatef(3.6, 0., 0.); // on décale de 4 vers la droite (x)
            glScalef(0.4, 0.4, 0.4); // Resize du plan
            drawCircle(50); // Dessin du cercle déplacé
        glPopMatrix(); // Reload de la matrice sauvegardée

}

void drawArm(){
	    glPushMatrix(); 
			glScalef(0.5, 0.5, 0.5); // Resize du plan
			glRotatef(alpha, 0., 0., 1.0);
            drawMainArm(); 
        glPopMatrix(); 

		glPushMatrix(); 
			glTranslatef(2.5, 2, 0.);
			glScalef(0.6, 0.6, 0.6);
			drawSecondArm();
		glPopMatrix(); 

}


int main(int argc, char** argv) 
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(4.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* RENDER HERE */
		drawOrigin();
		drawArm();
		//drawRoundedSquare();
		//drawSecondArm();

		// drawDrummer();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS) 
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}
	}

	glfwTerminate();
	return 0;
}
