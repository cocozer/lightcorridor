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
};