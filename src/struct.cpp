#include "struct.h"
#include "3D_tools.h"

// Struct Raquette fonctions
void Raquette::drawRaquette() {
    glColor3f(255, 255, 255); // Blanc
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(this->x, this->y, this->z); // Déplacement du plan pour correspondre au x et au y de la raquette
        glPushMatrix(); // Sauvegarde de la matrice
            glScalef(this->coefftaille, 1, this->coefftaille); // Resize du plan pour correspondre au coeff de la raquette
            drawSquare(); // Dessin de la raquette7
        glPopMatrix(); // Reload de la matrice sauvegardée
    glPopMatrix(); // Reload de la matrice sauvegardée
    
}

void Ball::drawBall() {
    glColor3f(0, 255, 0); // Vert
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(this->x, this->y, this->z); // Déplacement du plan pour correspondre au x, au y et au z de la balle
        glPushMatrix(); // Sauvegarde de la matrice
            glScalef(this->coefftaille, this->coefftaille, this->coefftaille); // Resize du plan pour correspondre au coeff de la balle
            drawSphere();
        glPopMatrix(); // Reload de la matrice sauvegardée
    glPopMatrix(); // Reload de la matrice sauvegardée
}

void Ball::updatePosition() {
    this->x += this->vx;
    this->y += this->vy;
    this->z += this->vz;
}

void Corridor::drawCorridor() {
    glColor3f(255, 255, 255); // Blanc
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(0, this->y, 0); // Déplacement du plan pour correspondre au y du couloir
        for(int i=0; i<12; i++) {
            glPushMatrix(); // Sauvegarde de la matrice
                glTranslatef(0, 0.2*i, 0);
                drawBorderCorridor();
            glPopMatrix(); // Reload de la matrice sauvegardée
        }
    glPopMatrix(); // Reload de la matrice sauvegardée
}