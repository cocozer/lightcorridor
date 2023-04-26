#include "struct.h"
#include "3D_tools.h"

// Struct Raquette fonctions
void Raquette::drawRaquette() {
    glColor3f(255, 255, 255); // Blanc
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(this->x, this->y, this->z); // Déplacement du plan pour correspondre au x et au y de la raquette
        
        glPushMatrix(); // Sauvegarde de la matrice
            glScalef(this->coefftaille, 1, this->coefftaille); // Resize du plan pour correspondre au coeff de la raquette
            drawSquare(); // Dessin de la raquette
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

void Obstacle::drawObstacle() {
    // if (this->y > 0.0025) {
    // glColor4f(1.0f, 0.0f, 1.0f, 0.01); // Définir la couleur avec une opacité de 0
    // //ça marche pas ???
    // } else {
    // glColor3f(0.0f, 0.0f, 1.0f); // Définir la couleur sans transparence
    // }
    glColor3f(0,0,255);
    if (this->side == 1) { //mur d'en haut
        glPushMatrix();
            glTranslatef(0, this->y, 2.5);
            drawUpsideWall();
            glPopMatrix();
    }

    if (this->side == 2) { //mur de droite
        glPushMatrix();
            glTranslatef(0, this->y, 0);
            drawRightWall();
            glPopMatrix();
    }

    if (this->side == 3) { //mur du bas
        glPushMatrix();
            glTranslatef(0, this->y, 0);//le meme mur que celui du haut mais décalé vers le bas
            drawUpsideWall();
            glPopMatrix();
    }

     if (this->side == 4) { //mur de gauche
        glPushMatrix();
            glTranslatef(-5, this->y, 0);//le meme mur que celui du haut mais décalé vers la gauche
            drawRightWall();
            glPopMatrix();
    }
}

void initList(ListOfObstacles* list){
    Obstacle *obstacle1 = new Obstacle;
    obstacle1->y=5;
    obstacle1->side=1;

    Obstacle *obstacle2 = new Obstacle;
    obstacle2->y=7;
    obstacle2->side=2;

    Obstacle *obstacle3 = new Obstacle;
    obstacle3->y=9;
    obstacle3->side=3;

    obstacle1->next=obstacle2;
    obstacle2->next=obstacle3;
    obstacle3->next = nullptr;

    //obstacle1->next = list->head; //le pointeur vers l'obstacle suivant devient le pointeur vers la tete de la liste
    list->head = obstacle1; // notre obstacle est placé à la tete de la liste
    //std::cout << "la liste est init" << std::endl;
}

void drawObstacles(ListOfObstacles* list){
    Obstacle* current = list->head;
    while(current!=nullptr){ //on parcoure la liste chaînée
      current->drawObstacle(); //on dessine chaque obstacle
      current = current->next;
    }
}