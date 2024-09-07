#include "common.h"
#include "Graphics.h"
#include "menus.h"
#include "sound.h"

int main(int argc, char** argv) {

    bool continuer = true;
    int selection = 0;

    // Initialisation
    initGraphics();

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        printf("Mix_OpenAudio Error: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    // Creer la fenetre d'affichage
    SDL_Window* window = SDL_CreateWindow("Fenetre principale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    CheckScreen(window, renderer);

    // Charger la police
    TTF_Font* font = TTF_OpenFont("data/PressStart2P-vaV7.ttf", 44);
    if (!font) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Créer une couleur pour le texte
    SDL_Color textColor = {107, 122, 151, 255};
    
    // Initialisation des pads (manettes)
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    TitleScreen(window, renderer, pad, &continuer);
    if (continuer) {
        while (continuer) {
            MainMenu(window, renderer, pad, font, &continuer, &selection, textColor);
            if (continuer) {
                Mix_Chunk* InGame = Mix_LoadWAV("data/sound/InGame.wav");
                CheckSound(InGame, window);
                Mix_PlayChannel(-1, InGame, -1);

                StartGame(selection, window, renderer, pad, font, textColor);

                Mix_HaltMusic();
                Mix_FreeChunk(InGame);
            }
        }
    }
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (font) TTF_CloseFont(font);
    Mix_CloseAudio();
    exitGraphics();

    return 0;
}
