#include <vector>
using namespace std;
struct Raquette {
    float x;
    float y;
    float z;
    float coefftaille;

    // Dessin de la raquette
    void drawRaquette();
};



struct Corridor {
    // Avancée du corridor vers le joueur 
    float y;

    // Dessin du corridor
    void drawCorridor();
};


struct Obstacle {
    // j'ai mis des _ avant les attributs pour ne pas avoir besoin de mettre this-> dans les fonctions 
    float _y; // Avancée de l'Obstacle vers le joueur 
    int _side; //entier pour chaque obstacle -> peut etre égal à 1, 2, 3 ou 4 (correspond au côté du mur : haut, droite, bas, gauche)
    float _size; // taille qui peut varier en cas de bonus ?
    // Obstacle* next = nullptr; //prochain obstacle de la liste chaînée

    //dessin de l'obstacle
    void drawObstacle();

    Obstacle(float y, int side); //constructeur
};

struct Ball {
    float x;
    float y;
    float z;

    float vx;
    float vy;
    float vz;

    float coefftaille;

    // Dessin de la balle
    void drawBall();

    // Update la position de la balle en fonction de sa vélocité en x, y et z
    void updatePosition();
    // Vérification de la direction de la balle pour savoir si elle heurte un bord du couloir et la faire rebondir
    void checkDirection();
    // Vérification de si la raquette touche la balle pour la faire rebondir
    void checkRaquetteHit(Raquette* raquette);
    // Vérifie si la balle est passée entre la raquette et la caméra
    bool checkLoose(Raquette* Raquette);

    void checkObstacleHit(Obstacle obstacle);
};

// void initList(ListOfObstacles* list);
 void drawObstacles(std::vector<Obstacle> obstacles); //pour dessiner tous les obstacles du vecteur
 void checkObstaclesHit(Ball ball, std::vector<Obstacle> obstacles);