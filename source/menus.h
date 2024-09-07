#ifndef MENUS_H
#define MENUS_H

void MainMenu(SDL_Window* window, SDL_Renderer* renderer, PadState pad, TTF_Font* font, bool *continuer, int *selection, SDL_Color textColor);

void StartGame(int selection, SDL_Window* window, SDL_Renderer* renderer, PadState pad, TTF_Font* font, SDL_Color textColor);

void TitleScreen(SDL_Window* window, SDL_Renderer* renderer, PadState pad, bool *continuer);

#endif