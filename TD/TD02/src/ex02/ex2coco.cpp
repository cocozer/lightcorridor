#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES // for C++
#include "GLFW/glfw3.h"
// #include "glad/glad.h"
#include <iostream>
#include <cmath>
#include "math.h"

#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <stdio.h>


const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
float xposprint[256];
float yposprint[256];
int itterateur = 0;
bool wemustclean = false;
bool lineloop = false;
int cooldown = 0;
int loopstate = 1;
static const float GL_VIEW_SIZE = 1.;
static float aspectRatio;

// float xtoprint[256];
// float ytoprint[256];
// int itterateur2 = 0;
/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Error handling function */
void onError(int error, const char* description) {
    std::cout << "GLFW Error: " << description << std::endl;
}

void onWindowResized(GLFWwindow* window,int width,int height){

    aspectRatio = width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if( aspectRatio > 1)
    {
        glOrtho(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
                 -1.0f, 1.0f);
    }
    else
    {
        glOrtho(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio, 
                 -1.0f, 1.0f);
    }
}

void drawOrigin() {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(-1., 0.);
    glVertex2f(1., 0.);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    glVertex2f(0., -1.);
    glVertex2f(0., 1.);
    glEnd();
}
void drawSquare() {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glEnd();
}

void drawCircle(int pts) {

    double rayon = 1.0;
  
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < pts; i++) {
        glVertex2f( rayon*cos(i*(2*M_PI/pts)) , rayon*sin(i*(2*M_PI/pts)));
    }
    //cout << "cos: "<< cos(M_PI/2) << "sin: "<< sin(M_PI/2) ;
    glEnd();


}

int main() {
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
#ifdef __APPLE__
    // We need to explicitly ask for a 3.3 context on Mac
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLTemplate", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     return -1;
    // }
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            double xpos, ypos;
            //getting cursor position
            glfwGetCursorPos(window, &xpos, &ypos);
            
            xposprint[itterateur] = xpos / (WINDOW_WIDTH/2);
            yposprint[itterateur] = ypos / (WINDOW_HEIGHT/2);

            xposprint[itterateur] = xposprint[itterateur] -1;
            yposprint[itterateur] = yposprint[itterateur] -1;

            yposprint[itterateur] = -yposprint[itterateur];
            // std::cout << "Cursor Position at (" << xposprint[itterateur] << " : " << yposprint[itterateur] << std::endl;
            itterateur++;
        }
    });
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == 256) {
            wemustclean = true;
        }
        if (key == 76) {
            if (cooldown == 0) {
                if (lineloop) {
                    lineloop = false;
                } else if (lineloop == false){
                    lineloop = true;
                }
                cooldown = 1;
            }

        }
        if(key == 66) {
            if (cooldown == 0) {
                loopstate++;
                if (loopstate > 3){
                    loopstate = 1;
                }
                cooldown = 1;
            }
        }
        std::cout << "key pressed: " << key << ", " << scancode << std::endl;
    });

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
        if (cooldown != 0) {
            cooldown++;
        }
        if (cooldown > 5) {
            cooldown = 0;
        }
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

        if(wemustclean) {
            for (int i=0; i<=itterateur; i++) {
                xposprint[i] = 0;
                yposprint[i] = 0;
            }
            wemustclean = false;
        }
        // // render exemple quad
        // glColor3f(1.0f, 0.0f, 0.0f);
        // glBegin(GL_QUADS);
        //     glVertex2f(-0.5f, -0.5f);
        //     glVertex2f(0.5f, -0.5f);
        //     glVertex2f(0.5f, 0.5f);
        //     glVertex2f(-0.5f, 0.5f);
        // glEnd();
        switch(loopstate){
            case 1 :
            drawOrigin();
            break;
            case 2 :  
            glPushMatrix();
            glRotatef(45, 0., 0., 1.);
            glTranslatef(0., 0.2f, 0.);
            drawSquare();
            glPopMatrix();
            break;
            case 3 :
            glPushMatrix();
            glTranslatef(0.5f, 0.5f, 0.5f);
            drawCircle(50);
            glPopMatrix();
            break;
        }
        // drawOrigin();
        // drawSquare();
        // drawCircle(50);
        // render points
        glBegin(GL_POINTS);
        glColor3f(1, 0, 0);
        glVertex2f(0., 0.);
        glVertex2f(0.5, 0.);
        glVertex2f(0., 0.5);
        glVertex2f(-0.5, -0.5);
        glEnd();
        

        // render clicked points
        if(lineloop) {
            glBegin(GL_LINE_LOOP);
        } else {
            glBegin(GL_POINTS);
        }
        glColor3f(1, 1, 1);
        for (int i=0; i<=itterateur; i++) {
            glVertex2f(xposprint[i], yposprint[i]);
        }
        
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