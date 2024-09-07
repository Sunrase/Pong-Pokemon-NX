#include "common.h"
#include "Pause.h"
#include "Graphics.h"

void Pause(SDL_Window* window, SDL_Renderer* renderer, PadState pad, TTF_Font* font, SDL_Color textColor) {

    SDL_Surface* Pause = TTF_RenderText_Solid(font, "Pause", textColor);
    CheckTextSurface(Pause, window, renderer, font);
    SDL_Texture* PauseTexture = SDL_CreateTextureFromSurface(renderer, Pause);
    SDL_FreeSurface(Pause);
    CheckTextTexture(PauseTexture, window, renderer, font);
    SDL_Rect PauseRect = {(SCREEN_W - Pause->w) / 2, (SCREEN_W - Pause->h) / 2, Pause->w, Pause->h};

    while (appletMainLoop())
    {
        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        if (kDown & HidNpadButton_Minus) {
            break;
        }
        
        // Nettoyer l'écran
        SDL_SetRenderDrawColor(renderer, 216, 200, 157, 255);
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, PauseTexture, NULL, &PauseRect);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS
    }
    SDL_DestroyTexture(PauseTexture);
}