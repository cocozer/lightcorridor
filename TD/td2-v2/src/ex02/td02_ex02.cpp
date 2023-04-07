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
using namespace std;

struct Vertex {
  double x,y;
};
vector<Vertex> tabMouseButtonCoordsHistory {};
int mode= GL_POINTS;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "TD02 Ex02";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 2.;

void drawPointFromMousePoint() {
	for (size_t i = 0; i < tabMouseButtonCoordsHistory.size(); i++)
	{
		glColor3f(1, 1, 1);
		glVertex2f(tabMouseButtonCoordsHistory[i].x, tabMouseButtonCoordsHistory[i].y);
	}
}

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
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    if (mode == GL_POINTS){
      mode=GL_LINE_LOOP;
    }
	}
}


void onMouseButton(GLFWwindow* window, int button, int action, int mods){
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){

     double xpos, ypos;

     //getting cursor position
     glfwGetCursorPos(window, &xpos, &ypos);

     double x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
     double y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

   Vertex mouseCoords = {x, y};

   tabMouseButtonCoordsHistory.push_back(mouseCoords);
  }


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
  //fermer la fenetre en cliquant sur Q
	glfwSetKeyCallback(window, onKey);


  // GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWwindow *window, GLFWmousebuttonfun callback)
  glfwSetMouseButtonCallback(window, onMouseButton);

  //glfwSetKeyCallback(window, drawloop);

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
    //GLBEGIN(GL_POINTS);
      //GLCOLOR3F(1, 0, 1);
      //DRAWPOINTFROMMOUSEPOINT();

      // dessiner ligne des points en cliquant sur M

      glBegin(mode);
      drawPointFromMousePoint();
      glEnd();


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
