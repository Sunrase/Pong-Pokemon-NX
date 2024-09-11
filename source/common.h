#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define RACKET_SPEED 12
#define ANGLE 60
#define FLAT_ANGLE 180
#define BALL_SIDE 75
#define SCREEN_W 1280
#define SCREEN_H 720
#define Y_RACKET SCREEN_H/2 - MIDDLE_OF_RACKET
#define RACKET_WIDTH 75
#define RACKET_LENGTH 225
#define MIDDLE_OF_RACKET RACKET_LENGTH/2
#define SPEED_INCREMENT 0.5f
#define MIN_SPEED 1.5f
#define ADDED_SPEED 0.5f
#define Y_LOGO 165
#define JOY_DEADZONE 8000  // Zone morte pour les axes du joystick

#endif