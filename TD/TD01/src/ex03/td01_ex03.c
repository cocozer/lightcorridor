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

/* Window size */
static const unsigned int WINDOW_WIDTH = 600;
static const unsigned int WINDOW_HEIGHT = 600;

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 1.;
// Nous representons ici les points situés en -0.5 et 0.5 en x et en y

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

static float aspectRatio;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window,int width,int height)
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
} 

int main(int argc, char** argv) 
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	glfwSetWindowSizeCallback (window, onWindowResized);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TD 01 EX 03", NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized(window,WINDOW_WIDTH, WINDOW_HEIGHT);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

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
