#ifndef GRAPHICS_H
#define GRAPHICS_H

void initGraphics();
void exitGraphics();
void CheckScreen(SDL_Window* window, SDL_Renderer* renderer);
void CheckImages(SDL_Surface *imageSurface, SDL_Window* window, SDL_Renderer* renderer);
void CheckTexture(SDL_Texture *Texture, SDL_Window* window, SDL_Renderer* renderer);
void CheckTextTexture(SDL_Texture *TextTexture, SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);
void CheckTextSurface(SDL_Surface *TextSurface, SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);

#endif