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
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(this->x, this->y, this->z); // Déplacement du plan pour correspondre au x, au y et au z de la balle
        // Dessin de l'ombre de la balle
        glPushMatrix();
        glTranslatef(0, 0, -this->z-0.37);
            glPushMatrix(); // Sauvegarde de la matrice
                glScalef(this->coefftaille, this->coefftaille, 0.1); // Resize du plan pour correspondre au coeff de la balle
                glColor3f(0, 0, 0); // Noir
                drawCircle();
            glPopMatrix(); // Reload de la matrice sauvegardée
        glPopMatrix(); // Reload de la matrice sauvegardée
        glPushMatrix(); // Sauvegarde de la matrice
            glScalef(this->coefftaille, this->coefftaille, this->coefftaille); // Resize du plan pour correspondre au coeff de la balle
            glColor3f(0, 255, 0); // Couleur de la balle
            drawSphere();
        glPopMatrix(); // Reload de la matrice sauvegardée
    glPopMatrix(); // Reload de la matrice sauvegardée
}

void Ball::updatePosition() {
    this->x += this->vx;
    this->y += this->vy;
    this->z += this->vz;
}

void Ball::checkDirection() {
    if(this->x < -0.5) {
        this->vx = -(this->vx);
    } else if(this->x > 0.5) {
        this->vx = -(this->vx);
    }

    if(this->z < -0.25) {
        this->vz = -(this->vz);
    } else if(this->z > 0.25) {
        this->vz = -(this->vz);
    }
}
void Ball::checkRaquetteHit(Raquette* raquette) {
    // Si la raquette touche la balle
    if (this->y < raquette->y) {
        if(this->x+0.2 > raquette->x - 0.25*raquette->coefftaille && this->z+0.2 > raquette->z - 0.25*raquette->coefftaille) { 
            if(this->x-0.2 < raquette->x + 0.25*raquette->coefftaille && this->z-0.2 < raquette->z + 0.25*raquette->coefftaille) { 
                
                this->vy = -this->vy; // On inverse la vitesse de la balle en y
            }
        }
    }
    
}

bool Ball::checkLoose(Raquette* raquette) {
    if(this->y < raquette->y) {
        return true;
    } else {
        return false;
    }
}

void Corridor::drawCorridor() {
    glColor3f(255, 255, 255); // Blanc
    for(int i=0; i<9; i++) {
        glPushMatrix(); // Sauvegarde de la matrice
        float translateY = (0.2*i)-this->y;
        while(translateY < 0) {
            translateY +=1.8;
        }
            glTranslatef(0, translateY, 0);
            drawBorderCorridor();
        glPopMatrix(); // Reload de la matrice sauvegardée
    }
}