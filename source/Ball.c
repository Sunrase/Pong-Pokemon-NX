#include "common.h"
#include "Ball.h"
#include <math.h>
#include <time.h>

void ballInit(SDL_Rect *BallRect, float speed[2]) {
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Choisir une direction aléatoire
    int choix = rand() % 2;
    float angle;
    
    if (choix == 0) {
        // Angle entre -ANGLE et +ANGLE degrés
        angle = (rand() % (2 * ANGLE + 1) - ANGLE) * (M_PI / 180.0f); // Convertir en radians
    } else {
        // Angle entre 180-ANGLE et 180+ANGLE degrés
        angle = (rand() % (2 * ANGLE + 1) + (FLAT_ANGLE - ANGLE)) * (M_PI / 180.0f); // Convertir en radians
    }

    // Définir la direction en utilisant cos et sin
    speed[0] = cos(angle);
    speed[1] = sin(angle);

    // Vérifier si la vitesse est trop lente et ajuster si nécessaire
    if ((speed[0] > 0 && speed[0] < MIN_SPEED)) speed[0] += ADDED_SPEED;
    if ((speed[0] < 0 && speed[0] > -MIN_SPEED)) speed[0] -= ADDED_SPEED;
    if ((speed[1] > 0 && speed[1] < MIN_SPEED)) speed[1] += ADDED_SPEED;
    if ((speed[1] < 0 && speed[1] > -MIN_SPEED)) speed[1] -= ADDED_SPEED;

    // Initialiser la position de la balle au centre de l'écran
    BallRect->x = SCREEN_W / 2 - BALL_SIDE / 2;
    BallRect->y = SCREEN_H / 2 - BALL_SIDE / 2;
}

// Increase speed when collision
void ImpSpeedCol(bool collision, float speed[2]) {
    if (collision & (speed[0] > 0)) speed[0] += SPEED_INCREMENT;
    if (collision & (speed[0] < 0)) speed[0] -= SPEED_INCREMENT;
    if (collision & (speed[1] > 0)) speed[1] += SPEED_INCREMENT;
    if (collision & (speed[1] < 0)) speed[1] -= SPEED_INCREMENT;
}

// Move the ball
void Movement(SDL_Rect *BallRect, float speed[2]) {
    BallRect->x += speed[0];
    BallRect->y += speed[1];
}