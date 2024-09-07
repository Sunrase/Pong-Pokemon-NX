#include "common.h"
#include "Graphics.h"
#include "relative_to_game.h"

// Update score and render it
void UpdateScoreText(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, int number, int number_2, SDL_Color color, SDL_Rect *Score_1Rect, SDL_Rect *Score_2Rect) {
    char numberStr[3];
    char numberStr_2[3];
    // Score 1
    snprintf(numberStr, sizeof(numberStr), "%d", number);

    SDL_Surface *Score_1Surface = TTF_RenderText_Solid(font, numberStr, color);
    CheckTextSurface(Score_1Surface, window, renderer, font);
    SDL_Texture *Score_1Texture = SDL_CreateTextureFromSurface(renderer, Score_1Surface);
    CheckTexture(Score_1Texture, window, renderer);

    Score_1Rect->w = Score_1Surface->w;
    Score_1Rect->h = Score_1Surface->h;

    SDL_FreeSurface(Score_1Surface);

    SDL_RenderCopy(renderer, Score_1Texture, NULL, Score_1Rect);

    SDL_DestroyTexture(Score_1Texture);

    // Score 2
    snprintf(numberStr_2, sizeof(numberStr_2), "%d", number_2);

    SDL_Surface *Score_2Surface = TTF_RenderText_Solid(font, numberStr_2, color);
    CheckTextSurface(Score_2Surface, window, renderer, font);
    SDL_Texture *Score_2Texture = SDL_CreateTextureFromSurface(renderer, Score_2Surface);
    CheckTexture(Score_2Texture, window, renderer);

    Score_2Rect->w = Score_2Surface->w;
    Score_2Rect->h = Score_2Surface->h;

    SDL_FreeSurface(Score_2Surface);
    
    SDL_RenderCopy(renderer, Score_2Texture, NULL, Score_2Rect);

    SDL_DestroyTexture(Score_2Texture);
    
}