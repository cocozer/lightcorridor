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
