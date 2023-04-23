#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <iostream>


#include "3D_tools.h"
#include "draw_scene.h"
#include "struct.h"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "TD04 Ex01";
static float aspectRatio = 1.0;

/* Etats du jeu */
bool play = true; // Est-ce que la partie est lancée ou pas ?
bool lose = false; // Est-ce que le joueur a perdu ?
bool CorridorMoving = false; // Est-ce que le couloir est en mouvement ou pas ?

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;

/* Error handling function */
void onError(int error, const char* description) {
    std::cout << "GLFW Error: " << description << std::endl;
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,aspectRatio,Z_NEAR,Z_FAR); // Fonctionnement de la caméra (ouverture, ratiojsp, distance mini d'affichage, distance max d'affichage)
	glMatrixMode(GL_MODELVIEW);
}

void MoveRaquette(GLFWwindow* window, Raquette* raquette) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

	xpos = ((xpos / (WINDOW_WIDTH/2))/2-0.5);
    ypos = -((ypos / (WINDOW_HEIGHT/2))/2-0.5);
	// On empêche de dépasser les bords de l'écran
	if (xpos < -0.43) { 
		xpos = -0.43;
	}
	if (xpos > 0.43) { 
		xpos = 0.43;
	}
	if (ypos < -0.43) { 
		ypos = -0.43;
	}
	if (ypos > 0.43) { 
		ypos = 0.43;
	}

    raquette->x = xpos*1.2*(raquette->y+1); // Position X multipliée par la sensibilité (change en fonction de la profondeur de la raquette)
    raquette->z = ypos*1.2*(raquette->y+1); // Position Y multipliée par la sensibilité (change en fonction de la profondeur de la raquette)

	
}

void MoveCorridor(Corridor* corridor, Ball* ball) {
	if(CorridorMoving) {
		corridor->y+=0.025;
		ball->y-=0.025;
	}
} 

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				// glfwSetWindowShouldClose(window, GLFW_TRUE); // Ferme la fenêtre 
				break;
			case GLFW_KEY_L :
				// glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				// glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			case GLFW_KEY_R :
				break;
			case GLFW_KEY_T :
				break;
			case GLFW_KEY_KP_9 :
				break;
			case GLFW_KEY_KP_3 :
				break;
			case GLFW_KEY_UP :
				if (CorridorMoving) {
					CorridorMoving = false;
				} else {
					CorridorMoving = true;
				}
				break;
			case GLFW_KEY_DOWN :
				break;
			case GLFW_KEY_LEFT :
				break;
			case GLFW_KEY_RIGHT :
				break;
			default:
				std::cout << "Touche non gérée (" << key << ")" << std::endl;
		}
	}
}

void mouse_button_callback(GLFWwindow* window ,int button, int action, int mods) {

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    {

    }

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
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
	
    if (!window) {
        glfwTerminate();
        return -1;
    }

	/* Création de la raquette */
	Raquette *raquette = new Raquette;
	raquette->x = 0;
	raquette->y = 1;
	raquette->z = 0;
	raquette->coefftaille = 1;

	/* Création de la balle */
	Ball *ball = new Ball;
	ball->x = 0;
	ball->y = 2;
	ball->z = 0;
	ball->vx = 0.01;
	ball->vy = -0.003;
	ball->vz = 0.01;
	ball->coefftaille = 0.1;

	/* Création du couloir */
	Corridor *corridor = new Corridor;
	corridor->y = 7.6;

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

    onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* On vérifie si le joueur a perdu */
		lose = ball->checkLoose(raquette);
		/* Updates des positions des objets*/
		ball->checkDirection(); // Balle (vérif de la direction de la balle pour collisions etc)
		ball->checkRaquetteHit(raquette); // rebond si la balle touche la raquette
		ball->updatePosition(); // update de la position de la balle
		MoveRaquette(window, raquette); // Raquette

		MoveCorridor(corridor, ball);

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Initial scenery setup */
		drawDecor();
		
		/* Draw Corridor*/
		corridor->drawCorridor();

		/* Draw Ball*/
		ball->drawBall();

		/* Draw Raquette */
		raquette->drawRaquette();

		/* Scene rendering */

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