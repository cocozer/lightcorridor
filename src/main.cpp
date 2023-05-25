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
bool play = false; // Est-ce que la partie est lancée ou pas ?
bool menupause = false; // Est-ce que le menu pause est affiché ou pas ?
bool menustart = true; // Est-ce que le menu start est affiché ou pas ?
bool menulose = false; // Est-ce que le menu lose est affiché ou pas ?
bool menuwin = false; // Est-ce que le menu win est affiché ou pas ?
bool lose = false; // Est-ce que le joueur a perdu ?
bool CorridorMoving = false; // Est-ce que le couloir est en mouvement ou pas ?
bool ballStick = false; // Si la balle est collée au milieu de la raquette
bool raquetteSticky = false; // Si la raquette est collante (grâce au bonus)
bool ballIsSticked = false; // Si la balle est collée à la raquette mais pas forcément au milieu
int effectDuration;
//bool raquetteObstacleCollision = false; //check si la raquette touche un obstacle

/* Variable globale du nombre de vies, 5 au départ*/
int lives = 5;
/* Variable globale balle pour pouvoir agir au clic gauche */
Ball *ball = new Ball;
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


void MoveCorridor(Corridor* corridor, Ball* ball, Raquette *raquette, std::vector<Obstacle>& obstacles, std::vector<Bonus>& bonuss) {
	if(CorridorMoving && (checkRaquetteObstacleCollison(raquette, obstacles)==false)) {
		corridor->y+=0.01;
		ball->y-=0.01;
		for(auto & obstacle : obstacles){
			obstacle._y-=0.01; //fait avancer l'obstacle
		}
		for(auto & bonus : bonuss){
			bonus._y-=0.01; //fait avancer le bonus
		}
	}
} 

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			// ...
			case GLFW_KEY_ESCAPE :
				menupause = true;
				play = false;
				break;
			case GLFW_KEY_UP :
				if(play) {
					CorridorMoving = true;
				}
				break;
			// ...
			default:
				std::cout << "Touche non gérée (" << key << ")" << std::endl;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch(key) {
			case GLFW_KEY_UP :
				if(play) {
					CorridorMoving = false;
				}
				break;
		}
	}
}


void mouse_button_callback(GLFWwindow* window ,int button, int action, int mods) {

	if(play) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    	{
			if(ballStick || ballIsSticked) {
				ball->vy = 0.02;
				ballStick = false;
				ballIsSticked = false;
			}
    	}
	} else {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    	{
			double mouseX, mouseY;
			float alpha = M_PI / 3; 
    		float d = 0.01; // distance entre la caméra et le centre du rectangle
			float h = tan(alpha / 2) * 2 * d;
        	glfwGetCursorPos(window, &mouseX, &mouseY);
			float newx = (mouseX - (WINDOW_WIDTH / 2)) * (h / WINDOW_HEIGHT);
    		float newz = -(mouseY - (WINDOW_HEIGHT / 2)) * (h / WINDOW_HEIGHT);

			if(newx > -0.0026 && newx < 0.0026 && newz > 0.0004 && newz < 0.0016) { // Si on clique sur le rect du haut
				menustart = false;
				menupause = false;
				menuwin = false;
				menulose = false;
				play = true;
			}
			
			if(newx > -0.0026 && newx < 0.0026 && newz < -0.0004 && newz > -0.0016) { // Si on clique sur le rect du bas
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
    	}
	}
	if(menupause) { // Si le menu est celui de

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

	/* Assignation des valeurs à la balle */

	ball->x = 0;
	ball->y = 3;
	ball->z = 0;
	ball->vx = 0.00;
	ball->vy = -0.015;
	ball->vz = 0.00;

	ball->coefftaille = 1;
	
	ballStick = true; // On colle la balle au début du jeu
	/* Création du couloir */
	Corridor *corridor = new Corridor;
	corridor->y = 0;
	/*Création du vecteur des obstacles*/

	//std::vector<Obstacle> obstacles ={Obstacle (1,1), Obstacle (1.4,2), Obstacle (1.8,3), Obstacle (2,4)};
	//std::vector<Obstacle> obstacles ={};

	std::vector<Obstacle> obstacles ={Obstacle (1,4), Obstacle (2,2), Obstacle (3,1), Obstacle (4,2), Obstacle (5,3), Obstacle (6,4), Obstacle (7,3), Obstacle (7.2,1), Obstacle (7.8,2), Obstacle (8,3), Obstacle (8.8,4), Obstacle (9,3), Obstacle (9,2)};

	/* Création du vecteur des Bonus */
	std::vector<Bonus> bonus ={Bonus (0.2,0.8,0,2), Bonus (0.2, 2.4, 0, 1), Bonus (-0.2,0.8,0, 1)};
	//std::vector<Bonus> bonus ={};
	

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
		
		if(lose) { // Si le joueur perd, on enlève une vie et on met colle la balle sur la raquette
			lose = false;
			lives--;
			cout << "vie en moins" << endl;
			ballStick = true;
			ball->vx = 0;
			ball->vy = 0;
			ball->vz = 0;
		}
		if(lives < 0) { // Si le joueur n'a plus de vies, la partie est perdue
			play = false;
			menulose = true;
			corridor->y = 0;
			// Reset tous les obstacles
			// Reset tous les bonus
		}
		if(play) { // Si la partie est lancée
			/* On vérifie si le joueur a perdu */
			lose = ball->checkLoose(raquette);
			/* Updates des positions des objets*/
			ball->checkDirection(); // Balle (vérif de la direction de la balle pour collisions etc)
			ball->checkObstaclesHit(obstacles);
			ballIsSticked = ball->checkRaquetteHit(raquette, raquetteSticky); // rebond si la balle touche la raquette
			if(ballIsSticked) {
				ball->vx = 0;
				ball->vy = 0;
				ball->vz = 0;
				ballStick = true;
			}
			ball->updatePosition(); // update de la position de la balle
			MoveRaquette(window, raquette); // Déplacement de la raquette (au mouvement de souris)
		}
		if(raquetteSticky) { // Si la raquette colle encore, on décrémente la durée de l'effet
			effectDuration--;
		}
		if (effectDuration <= 0) { // Si l'effet est arrivé a expiration, la raquette ne colle plus
			raquetteSticky = false;
		}
		

		MoveCorridor(corridor, ball, raquette, obstacles, bonus);

		if(ballStick) {
			ball->stickBall(raquette);
		}
		
		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Initial scenery setup */
		drawDecor();

		//checkRaquetteObstacleCollison(raquette, obstacles, raquetteObstacleCollision);
		//cout << raquetteObstacleCollision <<endl;


		if(menustart) {
			drawMenuStart();
		}
		if(menupause) {
			drawMenuPause();
		}
		if(menulose) {
			drawMenuLose();
		}
		if(menuwin) {
			drawMenuWin();
		}

		drawBonuss(bonus); //dessine le vecteur des bonus



		// ball->checkObstacleHit(obstacles[1]);
		int bonusactivation = checkBonussHit(*ball, bonus);
		if (bonusactivation == 1) {
			raquetteSticky = 1;
			effectDuration = 300; // L'effet dure 300 frames
		} else if (bonusactivation == 2) {
			lives++;
		}
		
		drawObstacles(obstacles); //dessine le vecteur des obstacles

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
		// /* If to few time is spend vs our wanted FPS, we wait */
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