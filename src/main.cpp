#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <iostream>
#include <vector>


#include "3D_tools.h"
#include "draw_scene.h"
#include "struct.h"
#include "math.h"

/* Window properties */
static unsigned int WINDOW_WIDTH = 1000;
static unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "TD04 Ex01";
static float aspectRatio = 1.0;

/* Etats du jeu */
bool play = true; // Est-ce que la partie est lancée ou pas ?
bool lose = false; // Est-ce que le joueur a perdu ?
bool CorridorMoving = false; // Est-ce que le couloir est en mouvement ou pas ?

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;


/* Error handling function */
void onError(int error, const char* description) {
    std::cout << "GLFW Error: " << description << std::endl;
}

void onWindowResized(GLFWwindow* window, int width, int height)
{

	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

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

	float alpha = M_PI/3; //angle de la camera sur le plan rectangulaire ou on veut mettre la raquette = 60degre
	float d = raquette->y; //distance camera et centre du rectangle
	float h = tan(alpha/2)*2*d;
	float newx = (xpos-(WINDOW_WIDTH/2))*(h/WINDOW_HEIGHT);
	float newz = (ypos-(WINDOW_HEIGHT/2))*(h/WINDOW_HEIGHT);

    raquette->x = newx; // Position X 
    raquette->z = -newz; // Position Y 

	if (raquette->x-raquette->coefftaille*0.1 < -0.5) {
		raquette->x = -0.5+raquette->coefftaille*0.1;
	}
	if (raquette->x+raquette->coefftaille*0.1 > 0.5) {
		raquette->x = 0.5-raquette->coefftaille*0.1;
	}
	if (raquette->z-raquette->coefftaille*0.1 < -0.25) {
		raquette->z = -0.25+raquette->coefftaille*0.1;
	}
	if (raquette->z+raquette->coefftaille*0.1 > 0.25) {
		raquette->z = 0.25-raquette->coefftaille*0.1;
	}
	

	//on veut passser du x et du z de la scène à celui de l'écran sans multiplier par 0.5

}

void MoveCorridor(Corridor* corridor, Ball* ball, std::vector<Obstacle>& obstacles) {
	if(CorridorMoving) {
		corridor->y+=0.01;
		ball->y-=0.01;
		for(auto & obstacle : obstacles){
			obstacle._y-=0.01; //fait avancer l'obstacle
		}
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

	//glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	/* Création de la raquette */
	Raquette *raquette = new Raquette;
	raquette->x = 0;
	raquette->y = 0.6;
	raquette->z = 0;
	raquette->coefftaille = 1;

	/* Création de la balle */
	Ball *ball = new Ball;
	ball->x = 0;
	ball->y = 3;
	ball->z = 0;
	ball->vx = 0.00;
	ball->vy = -0.003;
	ball->vz = 0.00;

	ball->coefftaille = 1;

	/* Création du couloir */
	Corridor *corridor = new Corridor;
	corridor->y = 0;

	/*Création du vecteur des obstacles*/

	// std::vector<Obstacle> obstacles ={Obstacle (1,1), Obstacle (1.2,2), Obstacle (1.4,3), Obstacle (1.6,4)};
	std::vector<Obstacle> obstacles ={Obstacle (5,1)};
	

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST); //Activation du z-buffer pour gérer la profondeur 

	/* Get time (in second) at loop beginning */
	double startTime = glfwGetTime();
	double deltaTime = 0.0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
        deltaTime = currentTime - startTime;
        startTime = currentTime;
		
		

		/* On vérifie si le joueur a perdu */
		lose = ball->checkLoose(raquette);
		/* Updates des positions des objets*/
		ball->checkDirection(); // Balle (vérif de la direction de la balle pour collisions etc)
		ball->checkRaquetteHit(raquette); // rebond si la balle touche la raquette
		ball->updatePosition(); // update de la position de la balle
		MoveRaquette(window, raquette); // Raquette

		MoveCorridor(corridor, ball, obstacles);

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Initial scenery setup */
		drawDecor();

		// obstacle1->drawObstacle();
		// obstacle2->drawObstacle();
		drawObstacles(obstacles); //dessine le vecteur des obstacles
		//checkObstaclesHit(*ball, obstacles);
		ball->checkObstacleHit(obstacles[1]);
		
		/* Draw Corridor*/
		corridor->drawCorridor();

		/* Draw Ball*/
		ball->drawBall();
		//std::cout<<"la balle a pour y" <<ball->y<<endl;

		/* Draw Raquette */
		raquette->drawRaquette();

		/* Scene rendering */

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		// double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		// if(elapsedTime < FRAMERATE_IN_SECONDS) 
		// {
		// 	glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		// }
		double endtime = startTime + FRAMERATE_IN_SECONDS;
		double currenttime = glfwGetTime();

		while(currenttime < endtime) {
			glfwWaitEventsTimeout(endtime-currenttime);
			currenttime = glfwGetTime();
		}

	}

    glfwTerminate();
    return 0;
}