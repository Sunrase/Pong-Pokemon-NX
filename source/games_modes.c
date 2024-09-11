<<<<<<< HEAD
#include "common.h"
#include "Graphics.h"
#include "Ball.h"
#include "Pause.h"
#include "relative_to_game.h"
#include "sound.h"

void Play_with_another_player(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font) {
    
    bool collision = false;
    float speed[2];   // Movement speed
    int score_player_1 = 0;
    int score_player_2 = 0;

    SDL_Surface *Map = IMG_Load("data/map.png");
    CheckImages(Map, window, renderer);
    SDL_Texture *MapTexture = SDL_CreateTextureFromSurface(renderer, Map);
    CheckTexture(MapTexture, window, renderer);
    SDL_Rect MapRect = { 0, 0, Map->w, Map->h };
    SDL_FreeSurface(Map);
    
    SDL_Surface *RaquetteGauche = IMG_Load("data/raquette_1.png");
    CheckImages(RaquetteGauche, window, renderer);
    SDL_Texture *RaquetteGaucheTexture = SDL_CreateTextureFromSurface(renderer, RaquetteGauche);
    CheckTexture(RaquetteGaucheTexture, window, renderer);
    SDL_Rect RaquetteGaucheRect = { 0, Y_RACKET, RaquetteGauche->w, RaquetteGauche->h };
        SDL_FreeSurface(RaquetteGauche);
    
    SDL_Surface *RaquetteDroite = IMG_Load("data/raquette_2.png");
    CheckImages(RaquetteDroite, window, renderer);
    SDL_Texture *RaquetteDroiteTexture = SDL_CreateTextureFromSurface(renderer, RaquetteDroite);
    CheckTexture(RaquetteDroiteTexture, window, renderer);
    SDL_Rect RaquetteDroiteRect = { SCREEN_W - RACKET_WIDTH, Y_RACKET, RaquetteDroite->w, RaquetteDroite->h };
    SDL_FreeSurface(RaquetteDroite);
    
    SDL_Surface *Ball = IMG_Load("data/ball.png");
    CheckImages(Ball, window, renderer);
    SDL_Texture *BallTexture = SDL_CreateTextureFromSurface(renderer, Ball);
    CheckTexture(BallTexture, window, renderer);
    SDL_Rect BallRect = { SCREEN_W/2 - BALL_SIDE/2, SCREEN_H/2 - BALL_SIDE/2, Ball->w, Ball->h };
    SDL_FreeSurface(Ball);
    
    SDL_Rect Score_1Rect = {756, 150, 0, 0};
    SDL_Rect Score_2Rect = {480, 150, 0, 0};

    ballInit(&BallRect, speed);

    Mix_Chunk* Bond = Mix_LoadWAV("data/sound/Bond.wav");
    CheckSound(Bond, window);

    // Boucle principale
    while (appletMainLoop()) {

        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        u32 kHeld = padGetButtons(&pad);
        HidAnalogStickState joystick_left = padGetStickPos(&pad, 0);
        HidAnalogStickState joystick_right = padGetStickPos(&pad, 1);

        // Moving rackets
        if ((kHeld & HidNpadButton_Down) || (joystick_left.y < -JOY_DEADZONE)) {
            if (RaquetteGaucheRect.y + RACKET_LENGTH + RACKET_SPEED <= SCREEN_H) RaquetteGaucheRect.y += RACKET_SPEED;
            else RaquetteGaucheRect.y += SCREEN_H - (RaquetteGaucheRect.y + RACKET_LENGTH);
        }    
        if ((kHeld & HidNpadButton_Up) || (joystick_left.y > JOY_DEADZONE)) {
            if (RaquetteGaucheRect.y - RACKET_SPEED > 0) RaquetteGaucheRect.y -= RACKET_SPEED;
            else RaquetteGaucheRect.y -= RaquetteGaucheRect.y;
        }

        if ((kHeld & HidNpadButton_B) || (joystick_right.y < -JOY_DEADZONE)) {
            if (RaquetteDroiteRect.y + RACKET_SPEED <= SCREEN_H - RACKET_LENGTH) RaquetteDroiteRect.y += RACKET_SPEED;
            else RaquetteDroiteRect.y += SCREEN_H - (RaquetteDroiteRect.y + RACKET_LENGTH);
        }  
        if ((kHeld & HidNpadButton_X) || (joystick_right.y > JOY_DEADZONE)) {
            if (RaquetteDroiteRect.y - RACKET_SPEED > 0) RaquetteDroiteRect.y -= RACKET_SPEED;
            else RaquetteDroiteRect.y -= RaquetteDroiteRect.y;
        }

        if (kDown & HidNpadButton_Minus) {
            Pause(window, renderer, pad, font, textColor);
        }

        if (kDown & HidNpadButton_Y) {
            break; // Break in order to return to the main loop
        }

        Movement(&BallRect, speed);

        // Detect collisions and reverse y axe
        if (BallRect.y <= 0 || BallRect.y >= SCREEN_H - BALL_SIDE) speed[1] = -speed[1], collision = true;

        // Collision left racket
        if (BallRect.x <= RACKET_WIDTH) {
            if ((BallRect.y + (BALL_SIDE/2) >= RaquetteGaucheRect.y) & (BallRect.y + (BALL_SIDE/2) <= RaquetteGaucheRect.y + RACKET_LENGTH)) {
                speed[0] = -speed[0];
                collision = true;
            } else {
                score_player_1 += 1;
                ballInit(&BallRect, speed);
            }
        }

        // Collision right racket
        if (BallRect.x + RACKET_WIDTH >= SCREEN_W - RACKET_WIDTH) {
            if ((BallRect.y + (BALL_SIDE/2) >= RaquetteDroiteRect.y) & (BallRect.y + (BALL_SIDE/2) <= RaquetteDroiteRect.y + RACKET_LENGTH)) {
                speed[0] = -speed[0];
                collision = true;
            } else {
                score_player_2 += 1;
                ballInit(&BallRect, speed);
            }
        }
        
        // Increase speed when collision
        ImpSpeedCol(collision, speed);

        // Nettoyer l'écran
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, MapTexture, NULL, &MapRect);
        UpdateScoreText(window, renderer, font, score_player_1, score_player_2, textColor, &Score_1Rect, &Score_2Rect); // Score update
        SDL_RenderCopy(renderer, RaquetteGaucheTexture, NULL, &RaquetteGaucheRect);
        SDL_RenderCopy(renderer, RaquetteDroiteTexture, NULL, &RaquetteDroiteRect);
        SDL_RenderCopy(renderer, BallTexture, NULL, &BallRect);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS

        if (collision) {
            collision = false;
            Mix_PlayChannel(-1, Bond, 0);
        }
    }
    Play_Back(window);
    Mix_FreeChunk(Bond);
    SDL_DestroyTexture(MapTexture);
    SDL_DestroyTexture(RaquetteGaucheTexture);
    SDL_DestroyTexture(RaquetteDroiteTexture);
    SDL_DestroyTexture(BallTexture);
}

void Unbeatable_AI(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font) {
    
    bool collision = false;
    float speed[2];   // Movement speed
    int score_player_1 = 0;
    int score_player_2 = 0;

    SDL_Surface *Map = IMG_Load("data/map.png");
    CheckImages(Map, window, renderer);
    SDL_Texture *MapTexture = SDL_CreateTextureFromSurface(renderer, Map);
    CheckTexture(MapTexture, window, renderer);
    SDL_Rect MapRect = { 0, 0, Map->w, Map->h };
    SDL_FreeSurface(Map);
    
    SDL_Surface *RaquetteGauche = IMG_Load("data/raquette_1.png");
    CheckImages(RaquetteGauche, window, renderer);
    SDL_Texture *RaquetteGaucheTexture = SDL_CreateTextureFromSurface(renderer, RaquetteGauche);
    CheckTexture(RaquetteGaucheTexture, window, renderer);
    SDL_Rect RaquetteGaucheRect = { 0, Y_RACKET, RaquetteGauche->w, RaquetteGauche->h };
    SDL_FreeSurface(RaquetteGauche);
    
    SDL_Surface *RaquetteDroite = IMG_Load("data/raquette_2.png");
    CheckImages(RaquetteDroite, window, renderer);
    SDL_Texture *RaquetteDroiteTexture = SDL_CreateTextureFromSurface(renderer, RaquetteDroite);
    CheckTexture(RaquetteDroiteTexture, window, renderer);
    SDL_Rect RaquetteDroiteRect = { SCREEN_W - RACKET_WIDTH, Y_RACKET, RaquetteDroite->w, RaquetteDroite->h };
    SDL_FreeSurface(RaquetteDroite);
    
    SDL_Surface *Ball = IMG_Load("data/ball.png");
    CheckImages(Ball, window, renderer);
    SDL_Texture *BallTexture = SDL_CreateTextureFromSurface(renderer, Ball);
    CheckTexture(BallTexture, window, renderer);
    SDL_Rect BallRect = { SCREEN_W/2 - BALL_SIDE/2, SCREEN_H/2 - BALL_SIDE/2, Ball->w, Ball->h };
    SDL_FreeSurface(Ball);
    
    SDL_Rect Score_1Rect = {756, 150, 0, 0};
    SDL_Rect Score_2Rect = {480, 150, 0, 0};

    ballInit(&BallRect, speed);

    Mix_Chunk* Bond = Mix_LoadWAV("data/sound/Bond.wav");
    CheckSound(Bond, window);

    // Boucle principale
    while (appletMainLoop()) {

        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        u32 kHeld = padGetButtons(&pad);
        HidAnalogStickState joystick_left = padGetStickPos(&pad, 0);

        // Moving rackets
        if ((kHeld & HidNpadButton_Down) || (joystick_left.y < -JOY_DEADZONE)) {
            if (RaquetteGaucheRect.y + RACKET_LENGTH + RACKET_SPEED <= SCREEN_H) RaquetteGaucheRect.y += RACKET_SPEED;
            else RaquetteGaucheRect.y += SCREEN_H - (RaquetteGaucheRect.y + RACKET_LENGTH);
        }    
        if ((kHeld & HidNpadButton_Up) || (joystick_left.y > JOY_DEADZONE)) {
            if (RaquetteGaucheRect.y - RACKET_SPEED > 0) RaquetteGaucheRect.y -= RACKET_SPEED;
            else RaquetteGaucheRect.y -= RaquetteGaucheRect.y;
        }

        // Moving right rakcet
        if ((BallRect.x > SCREEN_W/4) & (speed[0] > 0.0f)) {
            if ((BallRect.y < RaquetteDroiteRect.y+BALL_SIDE) & (RaquetteDroiteRect.y > 0)) {
                if (RaquetteDroiteRect.y - RACKET_SPEED > 0) RaquetteDroiteRect.y -= RACKET_SPEED;
                else RaquetteDroiteRect.y -= RaquetteDroiteRect.y;
            }

            if ((BallRect.y > RaquetteDroiteRect.y+BALL_SIDE) & (RaquetteDroiteRect.y + RACKET_LENGTH < SCREEN_H)) {
                if (RaquetteDroiteRect.y + RACKET_SPEED <= SCREEN_H - RACKET_LENGTH) RaquetteDroiteRect.y += RACKET_SPEED;
                else RaquetteDroiteRect.y += SCREEN_H - (RaquetteDroiteRect.y + RACKET_LENGTH);
            }
        }

        if (kDown & HidNpadButton_Minus) {
            Pause(window, renderer, pad, font, textColor);
        }

        if (kDown & HidNpadButton_Y) {
            break; // Break in order to return to the main loop
        }

        Movement(&BallRect, speed);

        // Detect collisions and reverse y axe
        if (BallRect.y <= 0 || BallRect.y >= SCREEN_H - BALL_SIDE) speed[1] = -speed[1], collision = true;

        // Collision left racket
        if (BallRect.x <= RACKET_WIDTH) {
            if ((BallRect.y + (BALL_SIDE/2) >= RaquetteGaucheRect.y) & (BallRect.y + (BALL_SIDE/2) <= RaquetteGaucheRect.y + RACKET_LENGTH)) {
                speed[0] = -speed[0];
                collision = true;
            } else {
                score_player_1 += 1;
                ballInit(&BallRect, speed);
            }
        }

        // Collision right racket
        if (BallRect.x + RACKET_WIDTH >= SCREEN_W - RACKET_WIDTH) {
            if ((BallRect.y + (BALL_SIDE/2) >= RaquetteDroiteRect.y) & (BallRect.y + (BALL_SIDE/2) <= RaquetteDroiteRect.y + RACKET_LENGTH)) {
                speed[0] = -speed[0];
                collision = true;
            } else {
                score_player_2 += 1;
                ballInit(&BallRect, speed);
            }
        }
        
        // Increase speed when collision
        ImpSpeedCol(collision, speed);

        // Nettoyer l'écran
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, MapTexture, NULL, &MapRect);
        UpdateScoreText(window, renderer, font, score_player_1, score_player_2, textColor, &Score_1Rect, &Score_2Rect); // Score update
        SDL_RenderCopy(renderer, RaquetteGaucheTexture, NULL, &RaquetteGaucheRect);
        SDL_RenderCopy(renderer, RaquetteDroiteTexture, NULL, &RaquetteDroiteRect);
        SDL_RenderCopy(renderer, BallTexture, NULL, &BallRect);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS

        if (collision) {
            collision = false;
            Mix_PlayChannel(-1, Bond, 0);
        }
    }
    Play_Back(window);
    Mix_FreeChunk(Bond);
    SDL_DestroyTexture(MapTexture);
    SDL_DestroyTexture(RaquetteGaucheTexture);
    SDL_DestroyTexture(RaquetteDroiteTexture);
    SDL_DestroyTexture(BallTexture);
}

void Play_against_wall(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font) {

    bool collision = false;
    float speed[2];   // Movement speed
    
    SDL_Surface *Map = IMG_Load("data/map.png");
    CheckImages(Map, window, renderer);
    SDL_Texture *MapTexture = SDL_CreateTextureFromSurface(renderer, Map);
    CheckTexture(MapTexture, window, renderer);
    SDL_Rect MapRect = { 0, 0, Map->w, Map->h };
    SDL_FreeSurface(Map);
    
    SDL_Surface *Raquette = IMG_Load("data/raquette.png");
    CheckImages(Raquette, window, renderer);
    SDL_Texture *RaquetteTexture = SDL_CreateTextureFromSurface(renderer, Raquette);
    CheckTexture(RaquetteTexture, window, renderer);
    SDL_Rect RaquetteRect = { SCREEN_W / 2 - Raquette->w/2, SCREEN_H - Raquette->h, Raquette->w, Raquette->h };
    SDL_FreeSurface(Raquette);
    
    SDL_Surface *Ball = IMG_Load("data/ball.png");
    CheckImages(Ball, window, renderer);
    SDL_Texture *BallTexture = SDL_CreateTextureFromSurface(renderer, Ball);
    CheckTexture(BallTexture, window, renderer);
    SDL_Rect BallRect = { SCREEN_W/2 - BALL_SIDE/2, SCREEN_H/2 - BALL_SIDE/2, Ball->w, Ball->h };
    SDL_FreeSurface(Ball);
    
    ballInit(&BallRect, speed);

    Mix_Chunk* Bond = Mix_LoadWAV("data/sound/Bond.wav");
    CheckSound(Bond, window);
    
    while (appletMainLoop())
    {
        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        u32 kHeld = padGetButtons(&pad);
        HidAnalogStickState joystick = padGetStickPos(&pad, 0);

        if (kDown & HidNpadButton_Y) {
            break; // Break in order to return to the main loop
        }

        // Moving rackets
        if ((kHeld & HidNpadButton_Right) || (joystick.x < -JOY_DEADZONE)) {
            if (RaquetteRect.x + RACKET_LENGTH + RACKET_SPEED <= SCREEN_W) RaquetteRect.x += RACKET_SPEED;
            else RaquetteRect.x += SCREEN_W - (RaquetteRect.x + RACKET_LENGTH);
        }    
        if ((kHeld & HidNpadButton_Left) || (joystick.x > JOY_DEADZONE)) {
            if (RaquetteRect.x - RACKET_SPEED > 0) RaquetteRect.x -= RACKET_SPEED;
            else RaquetteRect.x -= RaquetteRect.x;
        }

        Movement(&BallRect, speed);

        if (kDown & HidNpadButton_Minus) {
            Pause(window, renderer, pad, font, textColor);
        }
        if (BallRect.x <= 0 || BallRect.x >= SCREEN_W - BALL_SIDE) speed[0] = -speed[0], collision = true;
        if (BallRect.y <= 0) speed[1] = -speed[1], collision = true;

        // Collision racket
        if (BallRect.y + BALL_SIDE >= SCREEN_H - RACKET_WIDTH) {
            if ((BallRect.x + (BALL_SIDE/2) >= RaquetteRect.x) & (BallRect.x + (BALL_SIDE/2) <= RaquetteRect.x + RACKET_LENGTH)) {
                speed[1] = -speed[1];
                collision = true;
            } else {
                    ballInit(&BallRect, speed);

            }
        }

        ImpSpeedCol(collision, speed);
        
        // Nettoyer l'écran
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, MapTexture, NULL, &MapRect);
        SDL_RenderCopy(renderer, RaquetteTexture, NULL, &RaquetteRect);
        SDL_RenderCopy(renderer, BallTexture, NULL, &BallRect);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS

        if (collision) {
            collision = false;
            Mix_PlayChannel(-1, Bond, 0);
        }
    }
    Play_Back(window);
    Mix_FreeChunk(Bond);
    SDL_DestroyTexture(MapTexture);
    SDL_DestroyTexture(RaquetteTexture);
    SDL_DestroyTexture(BallTexture);
=======
#include "common.h"
#include "Graphics.h"
#include "Ball.h"
#include "Pause.h"
#include "relative_to_game.h"
#include "sound.h"

void Play_with_another_player(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font) {
    
    bool collision = false;
    float speed[2];   // Movement speed
    int score_player_1 = 0;
    int score_player_2 = 0;

    SDL_Surface *Map = IMG_Load("data/map.png");
    CheckImages(Map, window, renderer);
    SDL_Texture *MapTexture = SDL_CreateTextureFromSurface(renderer, Map);
    CheckTexture(MapTexture, window, renderer);
    SDL_Rect MapRect = { 0, 0, Map->w, Map->h };
    SDL_FreeSurface(Map);
    
    SDL_Surface *RaquetteGauche = IMG_Load("data/raquette_1.png");
    CheckImages(RaquetteGauche, window, renderer);
    SDL_Texture *RaquetteGaucheTexture = SDL_CreateTextureFromSurface(renderer, RaquetteGauche);
    CheckTexture(RaquetteGaucheTexture, window, renderer);
    SDL_Rect RaquetteGaucheRect = { 0, Y_RACKET, RaquetteGauche->w, RaquetteGauche->h };
        SDL_FreeSurface(RaquetteGauche);
    
    SDL_Surface *RaquetteDroite = IMG_Load("data/raquette_2.png");
    CheckImages(RaquetteDroite, window, renderer);
    SDL_Texture *RaquetteDroiteTexture = SDL_CreateTextureFromSurface(renderer, RaquetteDroite);
    CheckTexture(RaquetteDroiteTexture, window, renderer);
    SDL_Rect RaquetteDroiteRect = { SCREEN_W - RACKET_WIDTH, Y_RACKET, RaquetteDroite->w, RaquetteDroite->h };
    SDL_FreeSurface(RaquetteDroite);
    
    SDL_Surface *Ball = IMG_Load("data/ball.png");
    CheckImages(Ball, window, renderer);
    SDL_Texture *BallTexture = SDL_CreateTextureFromSurface(renderer, Ball);
    CheckTexture(BallTexture, window, renderer);
    SDL_Rect BallRect = { SCREEN_W/2 - BALL_SIDE/2, SCREEN_H/2 - BALL_SIDE/2, Ball->w, Ball->h };
    SDL_FreeSurface(Ball);
    
    SDL_Rect Score_1Rect = {756, 150, 0, 0};
    SDL_Rect Score_2Rect = {480, 150, 0, 0};

    ballInit(&BallRect, speed);

    Mix_Chunk* Bond = Mix_LoadWAV("data/sound/Bond.wav");
    CheckSound(Bond, window);

    // Boucle principale
    while (appletMainLoop()) {

        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        u32 kHeld = padGetButtons(&pad);
        HidAnalogStickState joystick_left = padGetStickPos(&pad, 0);
        HidAnalogStickState joystick_right = padGetStickPos(&pad, 1);

        // Moving rackets
        if ((kHeld & HidNpadButton_Down) || (joystick_left.y < -JOY_DEADZONE)) {
            if (RaquetteGaucheRect.y + RACKET_LENGTH + RACKET_SPEED <= SCREEN_H) RaquetteGaucheRect.y += RACKET_SPEED;
            else if (RaquetteGaucheRect.y + RACKET_LENGTH + RACKET_SPEED > SCREEN_H) RaquetteGaucheRect.y += SCREEN_H - (RaquetteGaucheRect.y + RACKET_LENGTH);
        }    
        if ((kHeld & HidNpadButton_Up) || (joystick_left.y > JOY_DEADZONE)) {
            if (RaquetteGaucheRect.y - RACKET_SPEED > 0) RaquetteGaucheRect.y -= RACKET_SPEED;
            else RaquetteGaucheRect.y -= RaquetteGaucheRect.y;
        }

        if ((kHeld & HidNpadButton_B) || (joystick_right.y < -JOY_DEADZONE)) {
            if (RaquetteDroiteRect.y + RACKET_SPEED <= SCREEN_H - RACKET_LENGTH) RaquetteDroiteRect.y += RACKET_SPEED;
            else if (RaquetteDroiteRect.y + RACKET_LENGTH + RACKET_SPEED > SCREEN_H) RaquetteDroiteRect.y += SCREEN_H - (RaquetteDroiteRect.y + RACKET_LENGTH);
        }  
        if ((kHeld & HidNpadButton_X) || (joystick_right.y > JOY_DEADZONE)) {
            if (RaquetteDroiteRect.y - RACKET_SPEED > 0) RaquetteDroiteRect.y -= RACKET_SPEED;
            else RaquetteDroiteRect.y -= RaquetteDroiteRect.y;
        }

        if (kDown & HidNpadButton_Minus) {
            Pause(window, renderer, pad, font, textColor);
        }

        if (kDown & HidNpadButton_Y) {
            break; // Break in order to return to the main loop
        }

        Movement(&BallRect, speed);

        // Detect collisions and reverse y axe
        if (BallRect.y <= 0 || BallRect.y >= SCREEN_H - BALL_SIDE) speed[1] = -speed[1], collision = true;

        // Collision left racket
        if (BallRect.x <= RACKET_WIDTH) {
            if ((BallRect.y + (BALL_SIDE/2) >= RaquetteGaucheRect.y) & (BallRect.y + (BALL_SIDE/2) <= RaquetteGaucheRect.y + RACKET_LENGTH)) {
                speed[0] = -speed[0];
                collision = true;
            } else {
                score_player_1 += 1;
                ballInit(&BallRect, speed);
            }
        }

        // Collision right racket
        if (BallRect.x + RACKET_WIDTH >= SCREEN_W - RACKET_WIDTH) {
            if ((BallRect.y + (BALL_SIDE/2) >= RaquetteDroiteRect.y) & (BallRect.y + (BALL_SIDE/2) <= RaquetteDroiteRect.y + RACKET_LENGTH)) {
                speed[0] = -speed[0];
                collision = true;
            } else {
                score_player_2 += 1;
                ballInit(&BallRect, speed);
            }
        }
        
        // Increase speed when collision
        ImpSpeedCol(collision, speed);

        // Nettoyer l'écran
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, MapTexture, NULL, &MapRect);
        UpdateScoreText(window, renderer, font, score_player_1, score_player_2, textColor, &Score_1Rect, &Score_2Rect); // Score update
        SDL_RenderCopy(renderer, RaquetteGaucheTexture, NULL, &RaquetteGaucheRect);
        SDL_RenderCopy(renderer, RaquetteDroiteTexture, NULL, &RaquetteDroiteRect);
        SDL_RenderCopy(renderer, BallTexture, NULL, &BallRect);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS

        if (collision) {
            collision = false;
            Mix_PlayChannel(-1, Bond, 0);
        }
    }
    Play_Back(window);
    Mix_FreeChunk(Bond);
    SDL_DestroyTexture(MapTexture);
    SDL_DestroyTexture(RaquetteGaucheTexture);
    SDL_DestroyTexture(RaquetteDroiteTexture);
    SDL_DestroyTexture(BallTexture);
}

void Unbeatable_AI(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font) {
    
    bool collision = false;
    float speed[2];   // Movement speed
    int score_player_1 = 0;
    int score_player_2 = 0;

    SDL_Surface *Map = IMG_Load("data/map.png");
    CheckImages(Map, window, renderer);
    SDL_Texture *MapTexture = SDL_CreateTextureFromSurface(renderer, Map);
    CheckTexture(MapTexture, window, renderer);
    SDL_Rect MapRect = { 0, 0, Map->w, Map->h };
    SDL_FreeSurface(Map);
    
    SDL_Surface *RaquetteGauche = IMG_Load("data/raquette_1.png");
    CheckImages(RaquetteGauche, window, renderer);
    SDL_Texture *RaquetteGaucheTexture = SDL_CreateTextureFromSurface(renderer, RaquetteGauche);
    CheckTexture(RaquetteGaucheTexture, window, renderer);
    SDL_Rect RaquetteGaucheRect = { 0, Y_RACKET, RaquetteGauche->w, RaquetteGauche->h };
        SDL_FreeSurface(RaquetteGauche);
    
    SDL_Surface *RaquetteDroite = IMG_Load("data/raquette_2.png");
    CheckImages(RaquetteDroite, window, renderer);
    SDL_Texture *RaquetteDroiteTexture = SDL_CreateTextureFromSurface(renderer, RaquetteDroite);
    CheckTexture(RaquetteDroiteTexture, window, renderer);
    SDL_Rect RaquetteDroiteRect = { SCREEN_W - RACKET_WIDTH, Y_RACKET, RaquetteDroite->w, RaquetteDroite->h };
    SDL_FreeSurface(RaquetteDroite);
    
    SDL_Surface *Ball = IMG_Load("data/ball.png");
    CheckImages(Ball, window, renderer);
    SDL_Texture *BallTexture = SDL_CreateTextureFromSurface(renderer, Ball);
    CheckTexture(BallTexture, window, renderer);
    SDL_Rect BallRect = { SCREEN_W/2 - BALL_SIDE/2, SCREEN_H/2 - BALL_SIDE/2, Ball->w, Ball->h };
    SDL_FreeSurface(Ball);
    
    SDL_Rect Score_1Rect = {756, 150, 0, 0};
    SDL_Rect Score_2Rect = {480, 150, 0, 0};

    ballInit(&BallRect, speed);

    Mix_Chunk* Bond = Mix_LoadWAV("data/sound/Bond.wav");
    CheckSound(Bond, window);

    // Boucle principale
    while (appletMainLoop()) {

        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        u32 kHeld = padGetButtons(&pad);
        HidAnalogStickState joystick_left = padGetStickPos(&pad, 0);

        // Moving rackets
        if ((kHeld & HidNpadButton_Down) || (joystick_left.y < -JOY_DEADZONE)) {
            if (RaquetteGaucheRect.y + RACKET_LENGTH + RACKET_SPEED <= SCREEN_H) RaquetteGaucheRect.y += RACKET_SPEED;
            else if (RaquetteGaucheRect.y + RACKET_LENGTH + RACKET_SPEED > SCREEN_H) RaquetteGaucheRect.y += SCREEN_H - (RaquetteGaucheRect.y + RACKET_LENGTH);
        }    
        if ((kHeld & HidNpadButton_Up) || (joystick_left.y > JOY_DEADZONE)) {
            if (RaquetteGaucheRect.y - RACKET_SPEED > 0) RaquetteGaucheRect.y -= RACKET_SPEED;
            else RaquetteGaucheRect.y -= RaquetteGaucheRect.y;
        }

        if ((BallRect.x > SCREEN_W/4) & (speed[0] > 0.0f)) {
            if ((BallRect.y < RaquetteDroiteRect.y+BALL_SIDE) & (RaquetteDroiteRect.y > 0)) RaquetteDroiteRect.y -= RACKET_SPEED;
            if ((BallRect.y > RaquetteDroiteRect.y+BALL_SIDE) & (RaquetteDroiteRect.y + RACKET_LENGTH < SCREEN_H)) RaquetteDroiteRect.y += RACKET_SPEED;
        }

        if (kDown & HidNpadButton_Minus) {
            Pause(window, renderer, pad, font, textColor);
        }

        if (kDown & HidNpadButton_Y) {
            break; // Break in order to return to the main loop
        }

        Movement(&BallRect, speed);

        // Detect collisions and reverse y axe
        if (BallRect.y <= 0 || BallRect.y >= SCREEN_H - BALL_SIDE) speed[1] = -speed[1], collision = true;

        // Collision left racket
        if (BallRect.x <= RACKET_WIDTH) {
            if ((BallRect.y + (BALL_SIDE/2) >= RaquetteGaucheRect.y) & (BallRect.y + (BALL_SIDE/2) <= RaquetteGaucheRect.y + RACKET_LENGTH)) {
                speed[0] = -speed[0];
                collision = true;
            } else {
                score_player_1 += 1;
                ballInit(&BallRect, speed);
            }
        }

        // Collision right racket
        if (BallRect.x + RACKET_WIDTH >= SCREEN_W - RACKET_WIDTH) {
            if ((BallRect.y + (BALL_SIDE/2) >= RaquetteDroiteRect.y) & (BallRect.y + (BALL_SIDE/2) <= RaquetteDroiteRect.y + RACKET_LENGTH)) {
                speed[0] = -speed[0];
                collision = true;
            } else {
                score_player_2 += 1;
                ballInit(&BallRect, speed);
            }
        }
        
        // Increase speed when collision
        ImpSpeedCol(collision, speed);

        // Nettoyer l'écran
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, MapTexture, NULL, &MapRect);
        UpdateScoreText(window, renderer, font, score_player_1, score_player_2, textColor, &Score_1Rect, &Score_2Rect); // Score update
        SDL_RenderCopy(renderer, RaquetteGaucheTexture, NULL, &RaquetteGaucheRect);
        SDL_RenderCopy(renderer, RaquetteDroiteTexture, NULL, &RaquetteDroiteRect);
        SDL_RenderCopy(renderer, BallTexture, NULL, &BallRect);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS

        if (collision) {
            collision = false;
            Mix_PlayChannel(-1, Bond, 0);
        }
    }
    Play_Back(window);
    Mix_FreeChunk(Bond);
    SDL_DestroyTexture(MapTexture);
    SDL_DestroyTexture(RaquetteGaucheTexture);
    SDL_DestroyTexture(RaquetteDroiteTexture);
    SDL_DestroyTexture(BallTexture);
}

void Play_against_wall(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font) {

    bool collision = false;
    float speed[2];   // Movement speed
    
    SDL_Surface *Map = IMG_Load("data/map.png");
    CheckImages(Map, window, renderer);
    SDL_Texture *MapTexture = SDL_CreateTextureFromSurface(renderer, Map);
    CheckTexture(MapTexture, window, renderer);
    SDL_Rect MapRect = { 0, 0, Map->w, Map->h };
    SDL_FreeSurface(Map);
    
    SDL_Surface *Raquette = IMG_Load("data/raquette.png");
    CheckImages(Raquette, window, renderer);
    SDL_Texture *RaquetteTexture = SDL_CreateTextureFromSurface(renderer, Raquette);
    CheckTexture(RaquetteTexture, window, renderer);
    SDL_Rect RaquetteRect = { SCREEN_W / 2 - Raquette->w/2, SCREEN_H - Raquette->h, Raquette->w, Raquette->h };
    SDL_FreeSurface(Raquette);
    
    SDL_Surface *Ball = IMG_Load("data/ball.png");
    CheckImages(Ball, window, renderer);
    SDL_Texture *BallTexture = SDL_CreateTextureFromSurface(renderer, Ball);
    CheckTexture(BallTexture, window, renderer);
    SDL_Rect BallRect = { SCREEN_W/2 - BALL_SIDE/2, SCREEN_H/2 - BALL_SIDE/2, Ball->w, Ball->h };
    SDL_FreeSurface(Ball);
    
    ballInit(&BallRect, speed);

    Mix_Chunk* Bond = Mix_LoadWAV("data/sound/Bond.wav");
    CheckSound(Bond, window);
    
    while (appletMainLoop())
    {
        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        u32 kHeld = padGetButtons(&pad);
        HidAnalogStickState joystick = padGetStickPos(&pad, 0);

        if (kDown & HidNpadButton_Y) {
            break; // Break in order to return to the main loop
        }

        // Moving rackets
        if ((kHeld & HidNpadButton_Right) || (joystick.x < -JOY_DEADZONE)) {
            if (RaquetteRect.x + RACKET_LENGTH + RACKET_SPEED <= SCREEN_W) RaquetteRect.x += RACKET_SPEED;
            else if (RaquetteRect.x + RACKET_LENGTH + RACKET_SPEED > SCREEN_W) RaquetteRect.x += SCREEN_W - (RaquetteRect.x + RACKET_LENGTH);
        }    
        if ((kHeld & HidNpadButton_Left) || (joystick.x > JOY_DEADZONE)) {
            if (RaquetteRect.x - RACKET_SPEED > 0) RaquetteRect.x -= RACKET_SPEED;
            else RaquetteRect.x -= RaquetteRect.x;
        }

        Movement(&BallRect, speed);

        if (kDown & HidNpadButton_Minus) {
            Pause(window, renderer, pad, font, textColor);
        }
        if (BallRect.x <= 0 || BallRect.x >= SCREEN_W - BALL_SIDE) speed[0] = -speed[0], collision = true;
        if (BallRect.y <= 0) speed[1] = -speed[1], collision = true;

        // Collision racket
        if (BallRect.y + BALL_SIDE >= SCREEN_H - RACKET_WIDTH) {
            if ((BallRect.x + (BALL_SIDE/2) >= RaquetteRect.x) & (BallRect.x + (BALL_SIDE/2) <= RaquetteRect.x + RACKET_LENGTH)) {
                speed[1] = -speed[1];
                collision = true;
            } else {
                    ballInit(&BallRect, speed);

            }
        }

        ImpSpeedCol(collision, speed);
        
        // Nettoyer l'écran
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, MapTexture, NULL, &MapRect);
        SDL_RenderCopy(renderer, RaquetteTexture, NULL, &RaquetteRect);
        SDL_RenderCopy(renderer, BallTexture, NULL, &BallRect);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS

        if (collision) {
            collision = false;
            Mix_PlayChannel(-1, Bond, 0);
        }
    }
    Play_Back(window);
    Mix_FreeChunk(Bond);
    SDL_DestroyTexture(MapTexture);
    SDL_DestroyTexture(RaquetteTexture);
    SDL_DestroyTexture(BallTexture);
>>>>>>> 75eef247746475ac28c48ef731ee8b5b4d444217
}