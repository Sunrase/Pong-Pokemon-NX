#include "common.h"
#include "Graphics.h"

void initGraphics() {
    romfsInit();
    chdir("romfs:/");

    // Initialisation de SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return ;
    }
}

void CheckScreen(SDL_Window* window, SDL_Renderer* renderer) {
    // Création de la fenêtre et du renderer
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return ;
    }

    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return ;
    }
}

void CheckImages(SDL_Surface *imageSurface, SDL_Window* window, SDL_Renderer* renderer) {
    if (!imageSurface) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        romfsExit();
        return ;
    }
}

void CheckTexture(SDL_Texture *Texture, SDL_Window* window, SDL_Renderer* renderer) {
    if (!Texture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

void CheckTextSurface(SDL_Surface *TextSurface, SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    if (!TextSurface) {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }
}

void CheckTextTexture(SDL_Texture *TextTexture, SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    if (!TextTexture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }
}

void exitGraphics() {
    SDL_Quit();
    TTF_Quit();
    romfsExit();
}