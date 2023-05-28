#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <iostream>
#include <vector>


#include "3D_tools.h"
#include "draw_scene.h"
#include "struct.h"
#include "math.h"
// #include "Texture.h"

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
int effectDurationStick; // Durée restant de l'effet stick
int effectDurationBigRaquette; // Durée restant de l'effet BigRaquette
bool canLose =false; //pour éviter la perte de 2 vies en meme temps
bool BallIsBetweenObstacleAndRaquette=false;
//bool raquetteObstacleCollision = false; //check si la raquette touche un obstacle

/* Variable globale du nombre de vies, 4 au départ*/
int lives = 4;
/* Variable globale balle pour pouvoir agir au clic gauche */
Ball *ball = new Ball;

/* Variable globale raquette */
Raquette *raquette = new Raquette;

/* Variable globale couloir*/
Corridor *corridor = new Corridor;

/*Création du vecteur des obstacles*/

//std::vector<Obstacle> obstacles ={Obstacle (1,1), Obstacle (1.4,2), Obstacle (1.8,3), Obstacle (2,4)};
// std::vector<Obstacle> obstacles ={};

std::vector<Obstacle> obstacles = {
    Obstacle(0.2, 3),
    Obstacle(1.0, 4),
    Obstacle(1.8, 1),
    Obstacle(2.6, 2),
    Obstacle(3.6, 2),
    Obstacle(4.8, 3),
    Obstacle(5.6, 3),
    Obstacle(6.6, 3),
    Obstacle(7.8, 2),
    Obstacle(8.6, 3),
    Obstacle(10.0, 4),
    Obstacle(10.8, 1),
    Obstacle(11.6, 2),
    Obstacle(12.6, 3),
    Obstacle(13.6, 1),
    Obstacle(14.6, 4),
    Obstacle(15.6, 3),
    Obstacle(16.8, 2),
    Obstacle(17.6, 3),
    Obstacle(18.6, 2),
    Obstacle(19.8, 1),
    Obstacle(20.6, 3),
    Obstacle(21.8, 2),
    Obstacle(22.6, 4),
    Obstacle(23.6, 1),
    Obstacle(24.8, 4),
    Obstacle(25.8, 3),
    Obstacle(26.8, 4),
    Obstacle(27.8, 2),
    Obstacle(28.6, 3),
    Obstacle(29.6, 2),
    Obstacle(30.8, 1),
    Obstacle(31.6, 2),
    Obstacle(32.8, 4),
    Obstacle(33.6, 1),
    Obstacle(34.6, 4),
    Obstacle(35.8, 2),
    Obstacle(36.6, 3),
    Obstacle(37.8, 1),
    Obstacle(38.8, 3),
    Obstacle(39.8, 1),
    Obstacle(40.8, 4),
    Obstacle(41.6, 2),
    Obstacle(42.8, 3),
    Obstacle(43.8, 2),
    Obstacle(44.8, 1),
    Obstacle(45.6, 3),
    Obstacle(46.8, 4),
    Obstacle(47.8, 2),
    Obstacle(48.6, 1),
    Obstacle(49.4, 4),
    Obstacle(50, 3),
};

/* Création du vecteur des Bonus */
std::vector<Bonus> bonus = {
	Bonus(0.0, 1, 0.1, 3),
    Bonus(0.0, 3.4, 0.1, 2),
    Bonus(-0.1, 7.0, -0.1, 2),
    Bonus(-0.1, 9.2, 0.2, 2),
    Bonus(0.1, 14.2, -0.2, 1),
    Bonus(-0.3, 17.4, 0.2, 2),
    Bonus(-0.3, 24.4, -0.2, 2),
    Bonus(0.2, 28.8, -0.1, 1),
    Bonus(-0.2, 31.8, -0.1, 1),
    Bonus(0.1, 35.0, -0.1, 2),
    Bonus(-0.2, 40.6, -0.2, 1),
    Bonus(-0.3, 46, -0.2, 1),
};


// std::vector<Bonus> bonus ={};

// Texture texture;
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

void ResetGame(Corridor* corridor, std::vector<Bonus>& bonuss, std::vector<Obstacle>& obstacles) {
	for (auto& bonus : bonuss) { // pour tous les éléments de bonus
		bonus._active = true;
		bonus._y += corridor->y;
	}
	for (auto& obstacle : obstacles) { // pour tous les éléments de obstacles
		obstacle._y += corridor->y;
	}
	ballStick = true;
	corridor->y = 0;
	lives = 5;
	CorridorMoving = false;
}

void MoveCorridor(Corridor* corridor, Ball* ball, Raquette *raquette, std::vector<Obstacle>& obstacles, std::vector<Bonus>& bonuss) {
	if(CorridorMoving && (checkRaquetteObstacleCollison(raquette, obstacles)==false)&&(!BallIsBetweenObstacleAndRaquette)) {
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
				canLose=true;
				cout<<canLose<<endl;
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
				if(newx > -0.0026 && newx < 0.0026 && newz > 0.0004 && newz < 0.0016) { // Si on clique sur le bouton du haut
					menustart = false;
					menupause = false;
					menuwin = false;
					menulose = false;
					play = true;
				}
			}
			if(newx > -0.0026 && newx < 0.0026 && newz < -0.0004 && newz > -0.0016) { // Si on clique sur le rect du bas
				if(newx > -0.0026 && newx < 0.0026 && newz < -0.0004 && newz > -0.0016) { // Si on clique sur le bouton du bas
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				}
			}
			if(menupause) { // Si le menu est celui de pause, alors on permet de reset la partie

				if(newx > -0.0015 && newx < 0.0015 && newz > 0.0027 && newz < 0.0034) { // Si on clique sur le bouton de reset de niveau (tout en haut)
					cout << "clic" << endl;
					// RESET LE NIVEAU
					ResetGame(corridor, bonus, obstacles);
					menupause = false;
					play = true;
				}
			}							
		}
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
	/* Assignation des valeurs à la raquette*/
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
	/* Set le couloir au départ*/
	corridor->y = 0;
	

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
			
	Texture texture = Texture::loadTexture("../doc/MetalGrate.jpg");
	Texture texture2 = Texture::loadTexture("../doc/fond.jpg");
	Texture textureplay = Texture::loadTexture("../doc/start.jpg");
	Texture textureexit = Texture::loadTexture("../doc/quit.jpg");
	Texture texture3 = Texture::loadTexture("../doc/cio60416.jpg");
	Texture vie = Texture::loadTexture("../doc/coeur.jpg");

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
			canLose=false;
			cout << "vie en moins" << endl;
			ballStick = true;
			ball->vx = 0;
			ball->vy = 0;
			ball->vz = 0;
		}
		if(lives < 0) { // Si le joueur n'a plus de vies, la partie est perdue
			play = false;
			menulose = true;
			ResetGame(corridor, bonus, obstacles);
		}
		if(play) { // Si la partie est lancée
			/* On vérifie si le joueur a perdu */
			if(canLose){
				lose = ball->checkLoose(raquette, canLose);
			}
			/* Updates des positions des objets*/
			ball->checkDirection(); // Balle (vérif de la direction de la balle pour collisions etc)
			
			if(corridor->y >= 50) { // Si le joueur dépasse 50 (unité d'avancement du couloir), il gagne
				play = false;
				CorridorMoving = false;
				menuwin = true;
				ResetGame(corridor, bonus, obstacles);
			}

			ballIsSticked = ball->checkRaquetteHit(raquette, raquetteSticky); // rebond si la balle touche la raquette
			ball->checkObstaclesHit(obstacles, BallIsBetweenObstacleAndRaquette);
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
			effectDurationStick--;
		}
		if (effectDurationStick <= 0) { // Si l'effet est arrivé a expiration, la raquette ne colle plus
			raquetteSticky = false;
		}
		if(raquette->coefftaille != 1){// Si la raquette n'a pas sa forme normale, on décrémente la durée de l'effet 
			effectDurationBigRaquette--;
		} 
		if (effectDurationBigRaquette <= 0) { // Si l'effet est arrivé a expiration, la raquette reprend sa taille initiale
			raquette->coefftaille = 1;
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

		if(menustart) {
			drawMenuStart(texture2, textureplay, textureexit);
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

		if(!menustart) {

			for (int i=0; i<=lives ; i++){
				glPushMatrix();
				glTranslatef(-0.02+i*0.008,0.1,0.055);
				glScalef(0.03,0.03,0.03);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,vie.textureID);
				// drawTexturedSphere(0.05, 20,20);
				drawTexturedSquare();
				glBindTexture(GL_TEXTURE_2D,0); //détache la texture du point de bind une fois les données chargées
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			glPushMatrix();
				//glRotatef(90,1,0,0);
				glTranslatef(-0.000,0.1001,0.055);
				glScalef(0.05,0.03,0.03);
				//glColor3f(0,0,0);
				drawRectangle();
			glPopMatrix();
		}				


		/* Draw Ball*/
		ball->drawBall(texture);
		

		/* Initial scenery setup */
		drawDecor();

		// checkRaquetteObstacleCollison(raquette, obstacles, raquetteObstacleCollision);
		//cout << raquetteObstacleCollision <<endl;



		drawBonuss(bonus); //dessine le vecteur des bonus



		// ball->checkObstacleHit(obstacles[1]);
		int bonusactivation = checkBonussHit(*ball, bonus);
		if (bonusactivation == 1) {
			raquetteSticky = 1;
			effectDurationStick = 300; // L'effet dure 300 frames
		} else if (bonusactivation == 2) {
			lives++;
		} else if (bonusactivation == 3) {
			effectDurationBigRaquette = 300; // L'effet dure 300 frames
			raquette->coefftaille = 1.5;
		}
		
		drawObstacles(obstacles); //dessine le vecteur des obstacles

		/* Draw Corridor*/
		corridor->drawCorridor();

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
	// glDeleteTextures(1,textures);
    glfwTerminate();
    return 0;
}