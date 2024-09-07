#include "common.h"
#include "animations.h"

void PointerAnimation(SDL_Rect *PointerRect, SDL_Rect Menu_L1Rect, float *mov) {
    if (PointerRect->x <= (Menu_L1Rect.x + (PointerRect->h / 2))) *mov = -*mov;
    else if (PointerRect->x >= Menu_L1Rect.x + PointerRect->w / 2 + 8) *mov = -*mov;
    PointerRect->x += *mov;
}

void LogoAnimation(SDL_Rect *LogoRect, int *mov_logo) {
    if (LogoRect->y <= Y_LOGO) {
        *mov_logo = 1;  // Aller vers le bas
    } else if (LogoRect->y >= Y_LOGO + 30) {
        *mov_logo = -1;  // Aller vers le haut
    }
    
    LogoRect->y += *mov_logo;
}