#include "struct.h"
#include "3D_tools.h"
#include <iostream>

// Struct Raquette fonctions
void Raquette::drawRaquette() {
    glColor3f(255, 255, 255); // Blanc
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(this->x, this->y, this->z); // Déplacement du plan pour correspondre au x et au y de la raquette
        // // Dessin de l'ombre de la raquette
        // glPushMatrix();
        // glTranslatef(0, 0, -this->z-0.25);
        //     glPushMatrix(); // Sauvegarde de la matrice
        //         glScalef(this->coefftaille, this->coefftaille, 0.05); // Resize du plan pour correspondre au coeff de la raquette
        //         glColor3f(0, 0, 0); // Noir
        //         drawSquare();
        //     glPopMatrix(); // Reload de la matrice sauvegardée
        // glPopMatrix(); // Reload de la matrice sauvegardée
        glPushMatrix(); // Sauvegarde de la matrice
            glScalef(this->coefftaille, 1, this->coefftaille); // Resize du plan pour correspondre au coeff de la raquette
            glColor3f(255, 255, 255); // Blanc
            drawSquare(); // Dessin de la raquette
        glPopMatrix(); // Reload de la matrice sauvegardée
    glPopMatrix(); // Reload de la matrice sauvegardée
    
}

void Ball::drawBall() {
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(this->x, this->y, this->z); // Déplacement du plan pour correspondre au x, au y et au z de la balle
        // Dessin de l'ombre de la balle
        glPushMatrix();
        glTranslatef(0, 0, -this->z-0.25);
            glPushMatrix(); // Sauvegarde de la matrice
                glScalef(this->coefftaille, this->coefftaille, 0.1); // Resize du plan pour correspondre au coeff de la balle
                glColor3f(0, 0, 0); // Noir
                drawCircle();
            glPopMatrix(); // Reload de la matrice sauvegardée
        glPopMatrix(); // Reload de la matrice sauvegardée
        glPushMatrix(); // Sauvegarde de la matrice
            glScalef(0.1*this->coefftaille, 0.1*this->coefftaille, 0.1*this->coefftaille); // Resize du plan pour correspondre au coeff de la balle
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
    if(this->x-this->coefftaille*0.1 < -0.5) {
        this->vx = -(this->vx);
    } else if(this->x+this->coefftaille*0.1 > 0.5) {
        this->vx = -(this->vx);
    }

    if(this->z-this->coefftaille*0.1 < -0.25) {
        this->vz = -(this->vz);
    } else if(this->z+this->coefftaille*0.1 > 0.25) {
        this->vz = -(this->vz);
    }
}
void Ball::checkRaquetteHit(Raquette* raquette) {
    // Si la raquette touche la balle et que la balle va vers le joueur
    if(this->vy < 0) {
        if (this->y-0.1*this->coefftaille <= raquette->y) { // Balle touche raquette en y
            if(this->x+0.2 >= raquette->x - 0.1*raquette->coefftaille && this->z+0.2 >= raquette->z - 0.1*raquette->coefftaille) { 
                if(this->x-0.2 <= raquette->x + 0.1*raquette->coefftaille && this->z-0.2 <= raquette->z + 0.1*raquette->coefftaille) { 
                    
                    this->vy = -this->vy; // On inverse la vitesse de la balle en y
                    cout<<"ça touche"<<endl;
                    //  // On calcule le coefficient de direction en fonction de l'endroit où touche la balle sur la raquette
                    float dx = this->x - raquette->x;
                    float dz = this->z - raquette->z;
                    if (dx < 0) {
                        this->vx -= 0.003;
                    } else if (dx > 0) {
                        this->vx += 0.003;
                    }

                    if (dz < 0) {
                        this->vz -= 0.003;
                    } else if (dz > 0) {
                        this->vz += 0.003;
                    }
                    float Coeffdx = 1+dx;
                    float Coeffdz = 1+dz;
                    this->vx = this->vx * Coeffdx;
                    this->vz = this->vz * Coeffdz;
                    cout<<this->vx<<endl;
                    cout<<this->vy<<endl;
                    cout<<this->vz<<endl;
                }
            }
        }
    }
}

void Ball::stickBall(Raquette* raquette) {
    this->x = raquette->x;
    this->y = raquette->y + 0.05;
    this->z = raquette->z;
}
void Ball::checkObstacleHit(Obstacle obstacle) {
    float delta = 0.01; // Marge d'erreur pour comparer deux nombres à virgule flottante

    // Vérifier si la balle se trouve dans la plage verticale de l'obstacle
    if ((this->y - 0.1 * this->coefftaille <= obstacle._y + delta) &&
        (this->y + 0.1 * this->coefftaille >= obstacle._y - delta)) {
        // Vérifier le côté de l'obstacle pour la collision
        switch (obstacle._side) {
            case 1: // Mur d'en haut
                this->vy = -this->vy; // Inverser la vitesse de la balle en y
                break;
            case 3: // Mur du bas
                this->vy = -this->vy; // Inverser la vitesse de la balle en y
                break;
            case 2: // Mur de droite
                this->vy = -this->vy; // Inverser la vitesse de la balle en y
                break;
            case 4: // Mur de gauche
                this->vx = -this->vx; // Inverser la vitesse de la balle en x
                break;
            default:
                break;
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


Obstacle::Obstacle(float y, int side){ // constructeur de la structure Obstacle
    _y=y;
    _side=side;
}



void Obstacle::drawObstacle() {
    if (_y > 5){
    glColor4f(1.0f, 0.0f, 1.0f, 0.0f); // Définir la couleur avec une opacité de 0
    //ça marche pas ???
    } else {
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Définir la couleur sans transparence
    //std::cout <<_y << endl;
    }
    //glColor3f(0,0,255);

    if (_side == 1) { //mur d'en haut
        glPushMatrix();
            glTranslatef(0, _y, 0);
            drawUpsideWall();
        glPopMatrix();
        //std::cout << "le mur d'en haut a pour y" << _y <<endl;
    }

    if (_side == 2) { //mur de droite
        glPushMatrix();
            glTranslatef(0, _y, 0);
            drawRightWall();
        glPopMatrix();
    }

    if (_side == 3) { //mur du bas
        glPushMatrix();
            glTranslatef(0, _y, -0.25);//le meme mur que celui du haut mais décalé vers le bas
            drawUpsideWall();
            glPopMatrix();
    }

    if (_side == 4) { //mur de gauche
        glPushMatrix();
            glTranslatef(-0.5, _y, 0);//le meme mur que celui du haut mais décalé vers la gauche
            drawRightWall();
            glPopMatrix();
    }
}

void drawObstacles(std::vector<Obstacle> obstacles){ //pour dessiner le vecteur des obstacles
  for (auto obstacle: obstacles) {//pour tous les éléments de obstacles
    obstacle.drawObstacle();
  }
}

void checkObstaclesHit(Ball ball, std::vector<Obstacle> obstacles){
    for (auto obstacle: obstacles) {//pour tous les éléments de obstacles
        ball.checkObstacleHit(obstacle);
    }

}