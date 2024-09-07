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
#define BALL_SIDE 80
#define SCREEN_W 1280
#define SCREEN_H 720
#define Y_RACKET SCREEN_H/2 - MIDDLE_OF_RACKET
#define RACKET_WIDTH 80
#define RACKET_LENGTH 240
#define SPEED_INCREMENT 1
#define MIN_SPEED 1.5
#define ADDED_SPEED 0.3
#define MIDDLE_OF_RACKET RACKET_LENGTH/2
#define RECTANGLE_WIDTH 35
#define RECTANGLE_LENGTH 380
#define Y_LOGO 165
#define JOY_DEADZONE 8000  // Zone morte pour les axes du joystick

#endif