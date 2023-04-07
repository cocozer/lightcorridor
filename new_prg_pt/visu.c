/* *******************************************************/
/* Exemple de programme OpenGL / GLFW           (C) 2010 */
/* Venceslas Biri   Université Paris Est Marne La Vallée */
/* *******************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

#include "visu.h"
#include "gldrawing.h"
#include "create_obj_pt.h"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Construction d'objet canonique par point";


/* variables globales pour la gestion de la caméra */
float profondeur = 3;
float latitude = 0.0;
float longitude = M_PI/2.;

float obj_rot = 0.0;
unsigned int size_pt = 5;
int flag_anim = 0;
int flag_run = 1;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	GLfloat  h = (GLfloat) width / (GLfloat) height ;
	
	/* dimension de l'écran GL */
	glViewport(0, 0, (GLint)width, (GLint)height);
	/* construction de la matrice de projection */
	glMatrixMode(GL_PROJECTION);
	float mat[16];
	computePerspectiveMatrix(mat,60.0,h,0.01,10.0);// Angle de vue, rapport largeur/hauteur, near, far
	glLoadMatrixf(mat);

	/* Retour a la pile de matrice Modelview
			et effacement de celle-ci */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				flag_run = 0;
				break;
			case GLFW_KEY_F :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			case GLFW_KEY_S :
				flag_anim = 1-flag_anim;
				break;
			case GLFW_KEY_KP_9 :
				if (profondeur>0.1+STEP_PROF) profondeur -= STEP_PROF;
				break;
			case GLFW_KEY_KP_3 :
				profondeur += STEP_PROF;
				break;
			case GLFW_KEY_UP :
				if (latitude>STEP_ANGLE) latitude -= STEP_ANGLE;
				break;
			case GLFW_KEY_DOWN :
				if(latitude<M_PI-STEP_ANGLE) latitude += STEP_ANGLE;
				break;
			case GLFW_KEY_LEFT :
				longitude -= STEP_ANGLE;
				break;
			case GLFW_KEY_RIGHT :
				longitude += STEP_ANGLE;
				break;
			default: fprintf(stdout,"Touche non gérée (%d)\n",key);
		}
	}
}

/*********************************************************/
/* fonction de dessin de la scène à l'écran              */
static void drawFunc(void) { 
	/* reinitialisation des buffers : couleur et ZBuffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* modification de la matrice de la scène */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Debut du dessin de la scène */
	glPushMatrix();
	
	/* placement de la caméra */
	float mat_v[16];
	float pos_cam[3] = {profondeur*sin(longitude)*sin(latitude),profondeur*cos(latitude),profondeur*cos(longitude)*sin(latitude)};
	float pt_viewed[3] = {0.f,0.f,0.f};
	float up_vec[3] = {0.0,1.0,0.0};
	computeLookAtMatrix(mat_v,pos_cam,pt_viewed,up_vec);
	glMultMatrixf(mat_v);

	
	glColor3f(1.0,0.0,1.0);
	glDrawRepere(2.0);

	float position[4] = {5.0,5.0,5.0,1.0};
	float black[3] = {0.0,0.0,0.0};
	float intensite[3] = {5.0,5.0,5.0};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,intensite);
	glLightfv(GL_LIGHT0,GL_SPECULAR,black);

	glPushMatrix();
	glRotatef(obj_rot,0.0,1.0,0.0);
	glColor3f(1.0,1.0,1.0);
	glDrawObject();

	glDisable(GL_LIGHTING);

	/* Fin du dessin */
	glPopMatrix();

	/* fin de la définition de la scène */
	glFinish();
}

/*********************************************************/
/* fonction d'initialisation des paramètres de rendu et  */
/* des objets de la scènes.                              */
void init() {
	profondeur = 3;
	latitude = M_PI/2.0;
	longitude = 0.0;

	obj_rot = 0.0;
	size_pt = 5;
	flag_anim = 0;
	flag_run = 1;

	/* INITIALISATION DES PARAMETRES GL */
	/* couleur du fond (gris sombre) */
	glClearColor(0.3,0.3,0.3,0.0);
	/* activation du ZBuffer */
	glEnable( GL_DEPTH_TEST);

	/* lissage des couleurs sur les facettes */
	glShadeModel(GL_SMOOTH);

	/* INITIALISATION DE LA SCENE */
	createCoordinates(&size_pt);
}

int main(int argc, char** argv) {
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

	init();

    while (flag_run)
    {
		// If animation is running update scene
		if (flag_anim) {
			obj_rot+=STEP_ANGLE;
		}
        // draw...
		drawFunc();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
    }

	return 0;
}
