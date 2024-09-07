#include "sound.h"

void CheckSound(Mix_Chunk *sound, SDL_Window* window) {
    if (!sound) {
        printf("Mix_LoadWAV Error: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

void Play_A_MAIN(SDL_Window *window) {
    Mix_Chunk* A_MAIN = Mix_LoadWAV("data/sound/A_MAIN.wav");
    CheckSound(A_MAIN, window);
    Mix_PlayChannel(-1, A_MAIN, 0);
    SDL_Delay(1014);
}

void Play_Back(SDL_Window *window) {
    Mix_Chunk* Back = Mix_LoadWAV("data/sound/Back.wav");
    CheckSound(Back, window);
    Mix_PlayChannel(-1, Back, 0);
    SDL_Delay(516);
}
