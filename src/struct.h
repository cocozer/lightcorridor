#include <vector>
using namespace std;
#include "Texture.h"

/*pour la gestion du rebond sur les obstacles*/
static int canBounce = 0;
static int counter = 0;

struct Raquette
{
    float x;
    float y;
    float z;
    float coefftaille;

    // Dessin de la raquette
    void drawRaquette();
    // Test de la collision avec les obstacles
    //  void checkObstacleCollision(Obstacle* obstacle);
    // void checkObstaclesCollision(std::vector<Obstacle> obstacles);
};

struct Corridor
{
    // Avancée du corridor vers le joueur
    float y;

    // Dessin du corridor
    void drawCorridor();
};

struct Bonus
{
    // Position du Bonus
    float _x;
    float _y;
    float _z;

    int _type; // Type du Bonus, peut être égal à 1 ou 2 ou 3
    // Dessin du Bonus
    bool _active;

    void drawBonus();

    Bonus(float x, float y, float z, int type);
};

struct Obstacle
{
    float _y;    // Avancée de l'Obstacle vers le joueur
    int _side;   // entier pour chaque obstacle -> peut etre égal à 1, 2, 3 ou 4 (correspond au côté du mur : haut, droite, bas, gauche)
    float _size; // taille qui peut varier en cas de bonus ?
    bool changeColor = false;
    // dessin de l'obstacle
    void drawObstacle();
    void changeColorObstacle();

    Obstacle(float y, int side); // constructeur
};

struct Ball
{
    float x;
    float y;
    float z;

    float vx;
    float vy;
    float vz;

    float coefftaille;

    // Dessin de la balle
    void drawBall(Texture &texture);

    // Update la position de la balle en fonction de sa vélocité en x, y et z
    void updatePosition();
    // Vérification de la direction de la balle pour savoir si elle heurte un bord du couloir et la faire rebondir
    void checkDirection();
    // Vérification de si la raquette touche la balle pour la faire rebondir
    bool checkRaquetteHit(Raquette *raquette, bool raquetteSticky);
    // Vérifie si la balle est passée entre la raquette et la caméra
    bool checkLoose(Raquette *Raquette, bool &canLose);

    void stickBall(Raquette *raquette);
    void checkObstaclesHit(std::vector<Obstacle> &obstacles, bool &BallIsBetweenObstacleAndRaquette);
    void checkObstacleHit(Obstacle &obstacle, bool &BallIsBetweenObstacleAndRaquette);

    int checkBonusHit(Bonus &bonus);
};

void drawObstacles(std::vector<Obstacle> obstacles); // pour dessiner tous les obstacles du vecteur
int checkBonussHit(Ball ball, std::vector<Bonus> &bonuss);

void drawBonuss(std::vector<Bonus> bonus); // pour dessiner tous les bonus du vecteur

bool checkRaquetteObstacleCollison(Raquette *raquette, std::vector<Obstacle> obstacles);
