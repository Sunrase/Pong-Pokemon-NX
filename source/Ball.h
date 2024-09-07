#ifndef BALL_H
#define BALL_H

void ballInit(SDL_Rect *BallRect, float speed[2]);

void ImpSpeedCol(bool collision, float speed[2]);

void Movement(SDL_Rect *BallRect, float speed[2]);

#endif