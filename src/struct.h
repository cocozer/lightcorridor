using namespace std;
struct Raquette {
    float x;
    float y;
    float z;
    float coefftaille;

    // Dessin de la raquette
    void drawRaquette();
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
};

struct Corridor {
    // Avancée du corridor vers le joueur 
    float y;

    // Dessin du corridor
    void drawCorridor();
};


struct Obstacle {
     // Avancée de l'Obstacle vers le joueur 
    float y;
    int side; //entier pour chaque obstacle -> peut etre égal à 1, 2, 3 ou 4 (correspond au côté du mur : haut, droite, bas, gauche)
    float size; // taille qui peut varier en cas de bonus ?
    Obstacle* next = nullptr; //prochain obstacle de la liste chaînée

    //dessin de l'obstacle
    void drawObstacle();
};

struct ListOfObstacles{
    Obstacle* head = nullptr;
    //faire une liste chainée qui contient les obstacles ?
    //les obstacles s'ajoutent au fur et à mesure que le joueur avance
    //leur side prend la valeur d'un random entre 1 et 4
    //un obstacle se supprime de la liste chainée lorsque son y dépasse la camera

    //void addObstacle();
    //void deleteObstacle();

};

void initList(ListOfObstacles* list);
void drawObstacles(ListOfObstacles *list); //pour dessiner tous les obstacles