#ifndef __VISU_CM_H
#define __VISU_CM_H

#define STEP_ANGLE	M_PI/90.
#define STEP_PROF	M_PI/90.
/* variables globales pour la gestion de la caméra */
extern float profondeur;
extern float latitude;
extern float longitude;

/* variables globales pour la gestion de l'objet */
extern float obj_rot;
extern unsigned int size_pt;
extern int flag_anim;
extern int flag_run;

/* Déclaration des fonctions */
void idle(void);
void init();

#endif
