#ifndef GAME_MODES_H
#define GAME_MODES_H

void Play_with_another_player(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font);

void Unbeatable_AI(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font);

void Play_against_wall(SDL_Window* window, SDL_Renderer* renderer, PadState pad, SDL_Color textColor, TTF_Font* font);

#endif