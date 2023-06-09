#include "struct.h"
#include "3D_tools.h"
#include <iostream>



// Struct Raquette fonctions
void Raquette::drawRaquette() {
    glColor3f(255, 255, 255); // Blanc
    glPushMatrix(); // Sauvegarde de la matrice
        glTranslatef(this->x, this->y, this->z); // Déplacement du plan pour correspondre au x et au y de la raquette
        glPushMatrix(); // Sauvegarde de la matrice
            glScalef(this->coefftaille, 1, this->coefftaille); // Resize du plan pour correspondre au coeff de la raquette
            glColor3f(255, 255, 255); // Blanc
            drawSquare(); // Dessin de la raquette
        glPopMatrix(); // Reload de la matrice sauvegardée
    glPopMatrix(); // Reload de la matrice sauvegardée
    
}


void Ball::drawBall(Texture& texture) {
		glPushMatrix();
            glTranslatef(this->x,this->y, this->z);
            glRotatef(90,1,0,0);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,texture.textureID);
            drawTexturedSphere(0.05, 20,20);
            glBindTexture(GL_TEXTURE_2D,0); //détache la texture du point de bind une fois les données chargées
            glDisable(GL_TEXTURE_2D);
		glPopMatrix();
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
bool Ball::checkRaquetteHit(Raquette* raquette, bool raquetteSticky) {
    // Si la raquette touche la balle et que la balle va vers le joueur
    if(this->vy < 0) {
        if (this->y-0.1*this->coefftaille <= raquette->y) { // Balle touche raquette en y
            if(this->x+0.05 >= raquette->x - 0.1 && this->z+0.05 >= raquette->z - 0.1*raquette->coefftaille) { 
                if(this->x-0.05 <= raquette->x + 0.1 && this->z-0.05 <= raquette->z + 0.1*raquette->coefftaille) { 
                    if(raquetteSticky) {
                        return true; // Si la raquette est collante, on retourne 1 pour coller la balle à la raquette
                    }
                    this->vy = -this->vy; // On inverse la vitesse de la balle en y
                    //  // On calcule le coefficient de direction en fonction de l'endroit où touche la balle sur la raquette
                    float dx = this->x - raquette->x;
                    float dz = this->z - raquette->z;
                    if (dx < 0) {
                        this->vx += 0.003;
                    } else if (dx > 0) {
                        this->vx -= 0.003;
                    }

                    if (dz < 0) {
                        this->vz += 0.003;
                    } else if (dz > 0) {
                        this->vz -= 0.003;
                    }
                    float Coeffdx = 1+dx;
                    float Coeffdz = 1+dz;
                    this->vx = this->vx * Coeffdx;
                    this->vz = this->vz * Coeffdz;
                    return false; // Si 0 est retourné, la balle rebondit normalement
                }
            }
        }
    }
    return false; // Si 0 est retourné, la balle n'est pas collée et n'a pas touché la raquette
}

void Ball::stickBall(Raquette* raquette) {
    this->x = raquette->x;
    this->y = raquette->y + 0.05;
    this->z = raquette->z;
}
void Ball::checkObstacleHit(Obstacle& obstacle, bool& BallIsBetweenObstacleAndRaquette) {
    float delta = 0.001; // Marge d'erreur pour comparer deux nombres à virgule flottante
    // Vérifier si la balle se trouve dans la plage verticale de l'obstacle
    counter +=1;
    if(counter ==15){
        counter =0;
        obstacle.changeColor=false;
    }
    if ((this->y - 0.05*this->coefftaille <= obstacle._y + delta) &&
        (this->y + 0.05*this->coefftaille >= obstacle._y - delta)) {
            canBounce+=1; //permet de ne faire rebondir qu'une fois la balle au lieu de plein de fois
        // Vérifier le côté de l'obstacle pour la collision
        if(canBounce==4){
            canBounce = 0; //on réinitialise la variable canBounce
           
            switch (obstacle._side) {
                case 1: // Mur d'en haut
                    if(this->z + 0.05*this->coefftaille >0){
                        this->vy=-this->vy; // Inverser la vitesse de la balle en y
                        this->vz=this->vz; //pour corriger les bugs de variation du z de la balle après rebond
                        this->vx=this->vx;
                         obstacle.changeColorObstacle();
                    }
                    break;
                case 2: // Mur de droite
                    if(this->x+ 0.05*this->coefftaille >0){
                        this->vy = -this->vy; // Inverser la vitesse de la balle en y
                        this->vz=this->vz; //pour corriger les bugs de variation du z de la balle après rebond
                        this->vx=this->vx;
                         obstacle.changeColorObstacle();
                    }
                    break;
                case 3: // Mur de bas
                    if(this->z-0.05*this->coefftaille <0){
                        this->vy = -this->vy; // Inverser la vitesse de la balle en y
                        this->vz=this->vz; //pour corriger les bugs de variation du z de la balle après rebond
                        this->vx=this->vx;
                         obstacle.changeColorObstacle();
                    }
                    break;
                case 4: // Mur de gauche
                    if(this->x- 0.05*this->coefftaille <0){
                        this->vy = -this->vy; // Inverser la vitesse de la balle en y
                        this->vz=this->vz; //pour corriger les bugs de variation du z de la balle après rebond
                        this->vx=this->vx;
                         obstacle.changeColorObstacle();
                    }
                    break;
                default:
                    break;
            }
        }
        if(this->y <0.75){ //pour stoper l'avancement du couloir si la balle se trouve entre la raquette et un mur ou juste devant un mur
            BallIsBetweenObstacleAndRaquette = true;
        } else {
            BallIsBetweenObstacleAndRaquette = false;
        }
    }
}

void Ball::checkObstaclesHit(std::vector<Obstacle>& obstacles, bool& BallIsBetweenObstacleAndRaquette){
    for (auto& obstacle: obstacles) { //pour tous les éléments de obstacles
        checkObstacleHit(obstacle, BallIsBetweenObstacleAndRaquette);
    }
}

int Ball::checkBonusHit(Bonus &bonus) {
    float rayon = 0.01; // Marge d'erreur pour comparer deux nombres à virgule flottante
    // Vérifier si la balle se trouve dans la plage verticale du bonus
    if ((this->y - 0.1 * this->coefftaille <= bonus._y + rayon) &&
        (this->y + 0.1 * this->coefftaille >= bonus._y - rayon)) {
        
        // Vérifier si la balle se trouve dans la plage horizontale du bonus
        if ((this->x - 0.1 * this->coefftaille <= bonus._x + rayon) &&
            (this->x + 0.1 * this->coefftaille >= bonus._x - rayon)) {
            
            // Vérifier si la balle se trouve dans la plage de profondeur du bonus
            if ((this->z - 0.1 * this->coefftaille <= bonus._z + rayon) &&
                (this->z + 0.1 * this->coefftaille >= bonus._z - rayon)) {
                bonus._active = false;
                if(bonus._type == 1) {
                    return 1;// Le premier bonus a été activé
                } else if (bonus._type == 2) {
                    return 2; // Le second bonus a été activé
                } else if (bonus._type == 3) {
                    return 3; // Le second bonus a été activé
                }
            }
        }
    }
    return 0; // Aucun bonus n'a été retourné
}



bool Ball::checkLoose(Raquette* raquette, bool& canLose) {
    if(this->y <raquette->y-0.1) {
        canLose=false;
        return true;

    } else {
        return false;
    }
}

void Corridor::drawCorridor() {
    glColor3f(255, 255, 255); // Blanc
    for(int i=0; i<27; i++) {
        glPushMatrix(); // Sauvegarde de la matrice
        float translateY = (0.2*i)-this->y;
        while(translateY < 0) {
            translateY +=5.4;
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

void Obstacle::changeColorObstacle(){
    this->changeColor=true;
}

Bonus::Bonus(float x, float y, float z, int type){ // constructeur de la structure Obstacle
    _x=x;
    _y=y;
    _z=z;
    _type=type;
}

void Bonus::drawBonus()  {

    rotationAngle += 1.0; // Augmenter l'angle de rotation
    if (rotationAngle >= 360.0) {
        rotationAngle =0; // Remise à zéro de l'angle
    }
    if((_type == 1)&&(_y>0.2)) {
        //bonus colle
        glPushMatrix(); // Sauvegarde de la matrice
            glTranslatef(_x,_y, _z); // Déplacement du pot de colle aux coordonnées spécifiées
            glPushMatrix(); // Sauvegarde de la matrice
                    glColor3f(255,255,255);
                    glTranslatef(0,-0.02,0.035);
                    glScalef(1,1,2.3);
                    drawScaledCube(0.25f,0,0);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0, 0, -_z-0.25);
                glPushMatrix(); // Sauvegarde de la matrice
                    glScalef(1, 1, 0.06);
                    glColor3f(0, 0, 0); // Noir
                    drawCircle();
                glPopMatrix(); // Reload de la matrice sauvegardée
            glPopMatrix(); // Reload de la matrice sauvegardée
            glPushMatrix(); // Sauvegarde de la matrice
                glScalef(0.03, 0.03, 0.1); // Resize du pot de colle
                glColor3f(1, 1, 0); // Blanc
                drawCone(); // Dessin de la partie supérieure du pot de colle
            glPopMatrix(); // Reload de la matrice sauvegardée
            
            glPushMatrix(); // Sauvegarde de la matrice
                glTranslatef(0, -0.03, 0); // Déplacement vers le bas pour dessiner la partie inférieure du pot de colle
                glScalef(0.03, 0.03, 0.03); // Resize du pot de colle en fonction de l'échelle spécifiée
                glColor3f(1, 1, 0); // Jaune
                drawSphere(); // Dessin de la partie inférieure du pot de colle
            glPopMatrix(); // Reload de la matrice sauvegardée
        glPopMatrix(); // Reload de la matrice sauvegardée
        
    } else if ((_type == 2)&&(_y>0.2)) {
        //bonus coeur qui rajoute une vie
       updateRotationAngle();
        glColor3f(255, 255, 255);
        glPushMatrix();
            glPushMatrix(); // Sauvegarde de la matrice
                glTranslatef(_x, _y, _z); // Déplacement du plan pour correspondre au x et au y du bonus
                    glTranslatef(0.02,0,0);
                    //glRotatef(rotationAngle, 0, 0, 1.); // Rotation autour de l'axe y
                    glPushMatrix(); // Sauvegarde de la matrice
                        glTranslatef(-0.02,0,-0.006);
                        glScalef(1.4,1,1);
                        drawScaledCube(0.25f,0,0);
                    glPopMatrix();
                    drawHeartCube();
            glPopMatrix(); // Reload 
            glPushMatrix(); //ombre du bonus
                glTranslatef(_x, _y, _z); // Déplacement du plan pour correspondre au x et au y du bonus
                glPushMatrix();
                    glTranslatef(0, 0, -_z-0.25);
                    glRotatef(90,1,0,0);
                    glScalef(0.4,0.3,0.3);
                    glColor3f(0, 0, 0); // Noir
                    drawFilledSquare();
                glPopMatrix();
            glPopMatrix(); // Reload de la matrice sauvegardée
        glPopMatrix();
        //cout << _y <<endl;
    } else if((_type == 3)&&(_y>0.2)) {
        //bonus/malus agrandissement de la raquette
        glColor3f(255,255,255);
        glPushMatrix(); // Sauvegarde de la matrice
            glTranslatef(_x, _y, _z); // Déplacement du plan pour correspondre au x et au y du bonus
                glTranslatef(0.02,0,0);
                glPushMatrix(); // Sauvegarde de la matrice
                    glTranslatef(-0.02,0,-0.006);
                    glScalef(1.4,1,1);
                    drawScaledCube(0.25f,0,0);
                glPopMatrix();
                drawArrow();
        glPopMatrix(); // Reload 
        glPushMatrix(); //ombre du bonus
                glTranslatef(_x, _y, _z); // Déplacement du plan pour correspondre au x et au y du bonus
                glPushMatrix();
                    glTranslatef(0, 0, -_z-0.25);
                    glRotatef(90,1,0,0);
                    glScalef(0.4,0.3,0.3);
                    glColor3f(0, 0, 0); // Noir
                    drawFilledSquare();
                glPopMatrix();
        glPopMatrix(); // Reload de la matrice sauvegardée
    }
}


void Obstacle::drawObstacle() {
    if(changeColor){
        glColor3f(0.7,0.9,1.0); //les murs deviennent bleu très clair lors de la collision avec la balle
    } else {
        if (_y > 2.0) {
        glColor3f(0.0, 0.0, 0.36); 
        } else if (_y > 1.6) {
            glColor3f(0.007, 0.24, 0.54);
        } else if (_y > 1.2) {
            glColor3f(0.0, 0.46, 0.7);
        } else if (_y > 0.8) {
            glColor3f(0.0, 0.58, 0.78);
        }else if (_y > 0.4) {
            glColor3f(0.0, 0.7, 0.84);
        }else {
            glColor3f(0.67, 0.9, 1.0);
        }
    }
  

    if (_y > 0.5){ //on ne dessine pas les murs qui sont trop proches

        if (_side == 1) { //mur d'en haut
            glPushMatrix();
                glTranslatef(0, _y, 0);
                drawUpsideWall();
            glPopMatrix();
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
}

void drawBonuss(std::vector<Bonus> bonuss){ //pour dessiner le vecteur des bonus
  for (auto bonus: bonuss) {//pour tous les éléments de bonus
    if(bonus._active) {
        bonus.drawBonus();
    }
  }
}

void drawObstacles(std::vector<Obstacle> obstacles){ //pour dessiner le vecteur des obstacles
  for (auto obstacle: obstacles) {//pour tous les éléments de obstacles
    obstacle.drawObstacle();
  }
}


int checkBonussHit(Ball ball, std::vector<Bonus>& bonuss){
    int bonusactivation = 0;
    for (auto& bonus : bonuss) {//pour tous les éléments de obstacles
        if(bonus._active == true) {
            bonusactivation = ball.checkBonusHit(bonus);
            if(bonusactivation != 0) { // Si un bonus a été activé, on retourne le bonus concerné
                return bonusactivation;
            }
        }
    }
    return bonusactivation;
}

bool checkRaquetteObstacleCollison(Raquette *raquette, std::vector<Obstacle> obstacles){
    float delta = 0.01;
    float raquetteDemiLargeur = (0.2*raquette->coefftaille)/2;
    for (auto obstacle: obstacles) { //pour tous les éléments de obstacles
        if((obstacle._y <0.62) && (obstacle._y>0.605)){
            //si l'obstacle est égal au y de la raquette + ou - delta 
            if(obstacle._side==1){//mur d'en haut
                if(raquette->z+raquetteDemiLargeur>0){
                    return true;
                }
            }
            if(obstacle._side==2){//mur de droite
                if(raquette->x+raquetteDemiLargeur>0){
                    return true;
                }
            }
            if(obstacle._side==3){//mur du bas
                if(raquette->z-raquetteDemiLargeur<0){
                    return true;
                }
            }
            if(obstacle._side==4){ //mur de gauche
                if(raquette->x-raquetteDemiLargeur<0){
                    return true;
                }
            }
        }
    }
    return false;
}