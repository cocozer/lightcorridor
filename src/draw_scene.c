#include "draw_scene.h"
#include "3D_tools.h"
#include <iostream>
float red = 0;
float green = 0;
float blue = 0;
void drawDecorX() {
    // Rectangle gauche
    glBegin(GL_QUADS);
		glVertex3f(-5,0,-2.5);
		glVertex3f(-5,2.5,-2.5);
		glVertex3f(-5,2.5,2.5);
		glVertex3f(-5,0,2.5);
	glEnd();

    // Rectangle droit
    glBegin(GL_QUADS);
		glVertex3f(5,0,-2.5);
		glVertex3f(5,2.5,-2.5);
		glVertex3f(5,2.5,2.5);
		glVertex3f(5,0,2.5);
    glEnd();
    
}
void drawDecorZ() {


    // Rectangle bas
    glBegin(GL_QUADS);
		glVertex3f(-5,0,-2.5);
		glVertex3f(-5,2.5,-2.5);
		glVertex3f(5,2.5,-2.5);
		glVertex3f(5,0,-2.5);
	glEnd();
    
    // Rectangle haut
    glBegin(GL_QUADS);
		glVertex3f(-5,0,2.5);
		glVertex3f(-5,2.5,2.5);
		glVertex3f(5,2.5,2.5);
		glVertex3f(5,0,2.5);
	glEnd();
}

void drawDecor() {
    // CADRE 1
    // Couleur
    red = 218.0/255; // Rouge
    green = 243.0/255; // Vert
    blue = 252.0/255; // Bleu
    glColor3f(red, green, blue);
    drawDecorX();
    // Couleur
    red = 198.0/255; // Rouge
    green = 236.0/255; // Vert
    blue = 250.0/255; // Bleu
    glColor3f(red, green, blue);
    drawDecorZ();

    // CADRE 2
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0, 2.5, 0); // Déplacement du plan
        // Couleur
        red = 161.0/255; // Rouge
        green = 224.0/255; // Vert
        blue = 247.0/255; // Bleu
        glColor3f(red, green, blue);
        drawDecorX();

        // Couleur
        red = 142.0/255; // Rouge
        green = 218.0/255; // Vert
        blue = 245.0/255; // Bleu
        glColor3f(red, green, blue);
        drawDecorZ();
        // CADRE 3
        glPushMatrix(); // Sauvegarde de la matrice
            glTranslatef(0, 2.5, 0); // Déplacement du plan
            // Couleur
            red = 105.0/255; // Rouge
            green = 205.0/255; // Vert
            blue = 242.0/255; // Bleu
            glColor3f(red, green, blue);
            drawDecorX();

            // Couleur
            red = 86.0/255; // Rouge
            green = 199.0/255; // Vert
            blue = 240.0/255; // Bleu
            glColor3f(red, green, blue);
            drawDecorZ();

            // CADRE 4
            glPushMatrix(); // Sauvegarde de la matrice
                glTranslatef(0, 2.5, 0); // Déplacement du plan
                // Couleur
                red = 49.0/255; // Rouge
                green = 187.0/255; // Vert
                blue = 237.0/255; // Bleu
                glColor3f(red, green, blue);
                drawDecorX();

                // Couleur
                red = 30.0/255; // Rouge
                green = 181.0/255; // Vert
                blue = 235.0/255; // Bleu
                glColor3f(red, green, blue);
                drawDecorZ();
                // CADRE 5
                glPushMatrix(); // Sauvegarde de la matrice
                    glTranslatef(0, 2.5, 0); // Déplacement du plan
                    // Couleur
                    red = 20.0/255; // Rouge
                    green = 170.0/255; // Vert
                    blue = 225.0/255; // Bleu
                    glColor3f(red, green, blue);
                    drawDecorX();

                    // Couleur
                    red = 18.0/255; // Rouge
                    green = 156.0/255; // Vert
                    blue = 206.0/255; // Bleu
                    glColor3f(red, green, blue);
                    drawDecorZ();
                    // CADRE 5
                    glPushMatrix(); // Sauvegarde de la matrice
                        glTranslatef(0, 2.5, 0); // Déplacement du plan
                        // Couleur
                        red = 15.0/255; // Rouge
                        green = 128.0/255; // Vert
                        blue = 169.0/255; // Bleu
                        glColor3f(red, green, blue);
                        drawDecorX();

                        // Couleur
                        red = 13.0/255; // Rouge
                        green = 114.0/255; // Vert
                        blue = 150.0/255; // Bleu
                        glColor3f(red, green, blue);
                        drawDecorZ();
                        // CADRE 6
                        glPushMatrix(); // Sauvegarde de la matrice
                            glTranslatef(0, 2.5, 0); // Déplacement du plan
                            // Couleur
                            red = 10.0/255; // Rouge
                            green = 85.0/255; // Vert
                            blue = 113.0/255; // Bleu
                            glColor3f(red, green, blue);
                            drawDecorX();

                            // Couleur
                            red = 8.0/255; // Rouge
                            green = 71.0/255; // Vert
                            blue = 94.0/255; // Bleu
                            glColor3f(red, green, blue);
                            drawDecorZ();
                            // CADRE 7
                            glPushMatrix(); // Sauvegarde de la matrice
                                glTranslatef(0, 2.5, 0); // Déplacement du plan
                                // Couleur
                                red = 5.0/255; // Rouge
                                green = 43.0/255; // Vert
                                blue = 56.0/255; // Bleu
                                glColor3f(red, green, blue);
                                drawDecorX();

                                // Couleur
                                red = 3.0/255; // Rouge
                                green = 29.0/255; // Vert
                                blue = 38.0/255; // Bleu
                                glColor3f(red, green, blue);
                                drawDecorZ();
                            glPopMatrix(); // Reload de la matrice sauvegardée
                        glPopMatrix(); // Reload de la matrice sauvegardée
                    glPopMatrix(); // Reload de la matrice sauvegardée
                glPopMatrix(); // Reload de la matrice sauvegardée
            glPopMatrix(); // Reload de la matrice sauvegardée
        glPopMatrix(); // Reload de la matrice sauvegardée
    glPopMatrix(); // Reload de la matrice sauvegardée
}

void drawMenuStart(){ 
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.011, 0); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(2, 2, 2); // Déplacement du plan pour prendre tout l'écran
            glColor3f(0, 0, 0); // NOIR
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, 0.001); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(0, 1, 0); // VERT
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée

    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, -0.001); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(1, 0, 0); // BLEU
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée
}

void drawMenuPause(){ 
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.011, 0); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(2, 2, 2); // Déplacement du plan pour prendre tout l'écran
            glColor3f(0, 0, 0); // NOIR
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, 0.001); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(0, 1, 0); // VERT
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée

    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, -0.001); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(1, 0, 0); // ROUGE
            drawRectangle(); // Dessin du bouton de menu
    glPopMatrix(); // Reload de la matrice sauvegardée

    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, 0.003); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(1, 1, 0); // JAUNE
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée
}

void drawMenuWin(){ 
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.011, 0); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(2, 2, 2); // Déplacement du plan pour prendre tout l'écran
            glColor3f(0, 0, 0); // NOIR
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, 0.001); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(0, 1, 0); // VERT
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée

    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, -0.001); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(1, 0, 0); // BLEU
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée
}

void drawMenuLose(){ 
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.011, 0); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(2, 2, 2); // Déplacement du plan pour prendre tout l'écran
            glColor3f(0, 0, 0); // NOIR
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, 0.001); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(0, 1, 0); // VERT
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée

    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0,0.01, -0.001); // Déplacement du plan pour être dans le champ de vision de la caméra
            glScalef(0.005, 0.005, 0.005); // Déplacement du plan pour former un bouton du menu
            glColor3f(1, 0, 0); // BLEU
            drawRectangle(); // Dessin de la partie inférieure du pot de colle
    glPopMatrix(); // Reload de la matrice sauvegardée
}
