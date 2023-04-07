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
#include <stdbool.h>

/* Window properties */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "TD02 Ex03";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 2.;

// bool isSquare;

int currentShape = 0;
int numShapes = 3;

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

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if(key == GLFW_KEY_F && action == GLFW_PRESS){
		// isSquare = !isSquare;
		currentShape = (currentShape + 1) % numShapes;
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
		 // eventuellement d’autres points …
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
void drawCircle(float cx, float cy, float r, int num_segments){
	glBegin(GL_POLYGON);
	float pi=3.1415926;
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0 * pi * ii / num_segments;//get the current angle

        float x = r * cos(theta);//calculate the x component
        float y = r * sin(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
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

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

        //dessin entre le clear et le swapbuffer
        // drawOrigin();
		// drawSquare();
		// drawCircle(0,0,1,360);

		// if (isSquare) {
        //     drawSquare(); // Dessine un carré si isSquare est vrai
        // } else {
        //     drawCircle(0,0,1,360); // Dessine un cercle sinon
        // }

		if (currentShape == 0) {
            drawSquare();
        } else if (currentShape == 1) {
            drawCircle(0,0,1,360);
        } else if (currentShape ==2){
			drawOrigin();
		}


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
