#include "common.h"
#include "Graphics.h"
#include "games_modes.h"
#include "animations.h"
#include "menus.h"
#include "sound.h"

void StartGame(int selection, SDL_Window* window, SDL_Renderer* renderer, PadState pad, TTF_Font* font, SDL_Color textColor) {
    if (selection == 0)
    {
        Play_with_another_player(window, renderer, pad, textColor, font);
    }
    if (selection == 1)
    {
        Play_against_wall(window, renderer, pad, textColor, font);
    }
    if (selection == 2)
    {
        Unbeatable_AI(window, renderer, pad, textColor, font);
    }
}

void MainMenu(SDL_Window* window, SDL_Renderer* renderer, PadState pad, TTF_Font* font, bool *continuer, int *selection, SDL_Color textColor) {

    SDL_Surface *Menu_Top = IMG_Load("data/Menu_Top.png");
    CheckImages(Menu_Top, window, renderer);
    SDL_Texture *Menu_TopTexture = SDL_CreateTextureFromSurface(renderer, Menu_Top);
    SDL_FreeSurface(Menu_Top);
    CheckTexture(Menu_TopTexture, window, renderer);
    SDL_Rect Menu_TopRect = { 0, 0, Menu_Top->w, Menu_Top->h };

    SDL_Surface *Menu_L1 = IMG_Load("data/Menu_L1.png");
    CheckImages(Menu_L1, window, renderer);
    SDL_Texture *Menu_L1Texture = SDL_CreateTextureFromSurface(renderer, Menu_L1);
    SDL_FreeSurface(Menu_L1);
    CheckTexture(Menu_L1Texture, window, renderer);
    SDL_Rect Menu_L1Rect = { (SCREEN_W - Menu_L1->w) / 2 - 20, 20, Menu_L1->w, Menu_L1->h };

    SDL_Surface *Menu_L2 = IMG_Load("data/Menu_L2.png");
    CheckImages(Menu_L2, window, renderer);
    SDL_Texture *Menu_L2Texture = SDL_CreateTextureFromSurface(renderer, Menu_L2);
    SDL_FreeSurface(Menu_L2);
    CheckTexture(Menu_L2Texture, window, renderer);
    SDL_Rect Menu_L2Rect = { (SCREEN_W - Menu_L2->w) / 2, Menu_L1Rect.h + 90, Menu_L2->w, Menu_L2->h };
    
    SDL_Surface *Menu_L3 = IMG_Load("data/Menu_L3.png");
    CheckImages(Menu_L3, window, renderer);
    SDL_Texture *Menu_L3Texture = SDL_CreateTextureFromSurface(renderer, Menu_L3);
    SDL_FreeSurface(Menu_L3);
    CheckTexture(Menu_L3Texture, window, renderer);
    SDL_Rect Menu_L3Rect = { (SCREEN_W - Menu_L3->w) / 2, Menu_L1Rect.h + Menu_L2Rect.h + 160, Menu_L3->w, Menu_L3->h };

    SDL_Surface *Menu_L2n2 = IMG_Load("data/Menu_L2.png");
    CheckImages(Menu_L2n2, window, renderer);
    SDL_Texture *Menu_L2n2Texture = SDL_CreateTextureFromSurface(renderer, Menu_L2n2);
    SDL_FreeSurface(Menu_L2n2);
    CheckTexture(Menu_L2n2Texture, window, renderer);
    SDL_Rect Menu_L2n2Rect = { (SCREEN_W - Menu_L2Rect.w) / 2, Menu_L1Rect.h + Menu_L2Rect.h + Menu_L3Rect.h + 230, Menu_L2n2->w, Menu_L2n2->h };

    SDL_Surface *Pointer = IMG_Load("data/pointer.png");
    CheckImages(Pointer, window, renderer);
    SDL_Texture *PointerTexture = SDL_CreateTextureFromSurface(renderer, Pointer);
    SDL_FreeSurface(Pointer);
    CheckTexture(PointerTexture, window, renderer);
    SDL_Rect PointerRect = { Menu_L1Rect.x + (Pointer->w / 2), Menu_L1Rect.h + 110, Pointer->w, Pointer->h };

    SDL_Surface* CGMSurface = TTF_RenderText_Solid(font, "Choose a game mode :", textColor);
    CheckTextSurface(CGMSurface, window, renderer, font);
    SDL_Texture* CGMTexture = SDL_CreateTextureFromSurface(renderer, CGMSurface);
    SDL_FreeSurface(CGMSurface);
    CheckTextTexture(CGMTexture, window, renderer, font);
    SDL_Rect CGMRect = {(SCREEN_W - Menu_L1Rect.w) / 2 + 15, 40, CGMSurface->w, CGMSurface->h};

    SDL_Surface* PWAPSurface = TTF_RenderText_Solid(font, "Play with another", textColor);
    CheckTextSurface(PWAPSurface, window, renderer, font);
    SDL_Texture* PWAPTexture = SDL_CreateTextureFromSurface(renderer, PWAPSurface);
    SDL_FreeSurface(PWAPSurface);
    CheckTextTexture(PWAPTexture, window, renderer, font);
    SDL_Rect PWAPRect = {(SCREEN_W - PWAPSurface->w) /2, Menu_L1Rect.h + 110, PWAPSurface->w, PWAPSurface->h};

    SDL_Surface* PWAPSurface2 = TTF_RenderText_Solid(font, "player", textColor);
    CheckTextSurface(PWAPSurface2, window, renderer, font);
    SDL_Texture* PWAPTexture2 = SDL_CreateTextureFromSurface(renderer, PWAPSurface2);
    SDL_FreeSurface(PWAPSurface2);
    CheckTextTexture(PWAPTexture2, window, renderer, font);
    SDL_Rect PWAPRect2 = {(SCREEN_W - PWAPRect.w) /2, Menu_L1Rect.h + 110 + PWAPSurface->h, PWAPSurface2->w, PWAPSurface2->h};

    SDL_Surface* PWTWSurface = TTF_RenderText_Solid(font, "Play with the wall", textColor);
    CheckTextSurface(PWTWSurface, window, renderer, font);
    SDL_Texture* PWTWTexture = SDL_CreateTextureFromSurface(renderer, PWTWSurface);
    SDL_FreeSurface(PWTWSurface);
    CheckTextTexture(PWTWTexture, window, renderer, font);
    SDL_Rect PWTWRect = {(SCREEN_W - PWTWSurface->w) / 2, Menu_L1Rect.h + Menu_L2Rect.h + 183, PWTWSurface->w, PWTWSurface->h};

    SDL_Surface* PAUASurface = TTF_RenderText_Solid(font, "Play against the", textColor);
    CheckTextSurface(PAUASurface, window, renderer, font);
    SDL_Texture* PAUATexture = SDL_CreateTextureFromSurface(renderer, PAUASurface);
    SDL_FreeSurface(PAUASurface);
    CheckTextTexture(PAUATexture, window, renderer, font);
    SDL_Rect PAUARect = {(SCREEN_W - PAUASurface->w) / 2 - 20, Menu_L1Rect.h + Menu_L2Rect.h + 335, PAUASurface->w, PAUASurface->h};

    SDL_Surface* PAUASurface2 = TTF_RenderText_Solid(font, "unbeatable AI", textColor);
    CheckTextSurface(PAUASurface2, window, renderer, font);
    SDL_Texture* PAUATexture2 = SDL_CreateTextureFromSurface(renderer, PAUASurface2);
    SDL_FreeSurface(PAUASurface2);
    CheckTextTexture(PAUATexture2, window, renderer, font);
    SDL_Rect PAUARect2 = {(SCREEN_W - PAUARect.w) / 2 - 20, Menu_L1Rect.h + Menu_L2Rect.h + 345 + PAUASurface->h, PAUASurface2->w, PAUASurface2->h};

    float mov = 1;

    Mix_Chunk* MainMenu = Mix_LoadWAV("data/sound/MainMenu.wav");
    CheckSound(MainMenu, window);
    Mix_PlayChannel(-1, MainMenu, -1);

    Mix_Chunk* Move = Mix_LoadWAV("data/sound/move.wav");
    CheckSound(Move, window);

    //Main Loop
    while (appletMainLoop())
    {
        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        
        if (kDown & HidNpadButton_Plus) {
            *continuer = false;
            break;
        }

        if (kDown & HidNpadButton_A) {
            Mix_HaltMusic();
            Mix_FreeChunk(MainMenu);
            Mix_FreeChunk(Move);
            Play_A_MAIN(window);
            break;
        }

        if (kDown & HidNpadButton_Down) if (*selection < 2) {
            *selection += 1;
            Mix_PlayChannel(-1, Move, 0);
        }
        if (kDown & HidNpadButton_Up) if (*selection > 0) {
            *selection -= 1;
            Mix_PlayChannel(-1, Move, 0);
        }

        if (*selection == 1) {
            PointerRect.y = Menu_L3Rect.y + 15;
        } else if (*selection == 2) {
            PointerRect.y = Menu_L2n2Rect.y + 15;
        } else if (PointerRect.y != Menu_L2Rect.y + 105) {
            PointerRect.y = Menu_L2Rect.y + 15;
        }

        PointerAnimation(&PointerRect, Menu_L1Rect, &mov);
        
        // Nettoyer l'écran
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, Menu_TopTexture, NULL, &Menu_TopRect);
        SDL_RenderCopy(renderer, Menu_L1Texture, NULL, &Menu_L1Rect);
        SDL_RenderCopy(renderer, Menu_L2Texture, NULL, &Menu_L2Rect);
        SDL_RenderCopy(renderer, Menu_L2n2Texture, NULL, &Menu_L2n2Rect);
        SDL_RenderCopy(renderer, Menu_L3Texture, NULL, &Menu_L3Rect);
        SDL_RenderCopy(renderer, PointerTexture, NULL, &PointerRect);
        SDL_RenderCopy(renderer, CGMTexture, NULL, &CGMRect);
        SDL_RenderCopy(renderer, PWAPTexture, NULL, &PWAPRect);
        SDL_RenderCopy(renderer, PWAPTexture2, NULL, &PWAPRect2);
        SDL_RenderCopy(renderer, PWTWTexture, NULL, &PWTWRect);
        SDL_RenderCopy(renderer, PAUATexture, NULL, &PAUARect);
        SDL_RenderCopy(renderer, PAUATexture2, NULL, &PAUARect2);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS
    }
    SDL_DestroyTexture(Menu_TopTexture);
    SDL_DestroyTexture(Menu_L1Texture);
    SDL_DestroyTexture(Menu_L2Texture);
    SDL_DestroyTexture(Menu_L2n2Texture);
    SDL_DestroyTexture(Menu_L3Texture);
    SDL_DestroyTexture(PointerTexture);
    SDL_DestroyTexture(CGMTexture);
    SDL_DestroyTexture(PWAPTexture);
    SDL_DestroyTexture(PWAPTexture2);
    SDL_DestroyTexture(PWTWTexture);
    SDL_DestroyTexture(PAUATexture);
    SDL_DestroyTexture(PAUATexture2);
}

void TitleScreen(SDL_Window* window, SDL_Renderer* renderer, PadState pad, bool *continuer) {

    int mov_logo = -1;
    int frame_count = 0;
    
    // Charger le fond
    SDL_Surface *MainBackground = IMG_Load("data/logo_background.png");
    CheckImages(MainBackground, window, renderer);
    SDL_Texture *MainBackgroundTexture = SDL_CreateTextureFromSurface(renderer, MainBackground);
    SDL_FreeSurface(MainBackground);
    CheckTexture(MainBackgroundTexture, window, renderer);
    SDL_Rect MainBackgroundRect = { 0, 0, MainBackground->w, MainBackground->h };

    // Charger le logo
    SDL_Surface *Logo = IMG_Load("data/logo.png");
    CheckImages(Logo, window, renderer);
    SDL_Texture *LogoTexture = SDL_CreateTextureFromSurface(renderer, Logo);
    SDL_FreeSurface(Logo);
    CheckTexture(LogoTexture, window, renderer);
    SDL_Rect LogoRect = { (SCREEN_W - Logo->w) / 2, Y_LOGO, Logo->w, Logo->h };

    // Charger Press A
    SDL_Surface *Press_A = IMG_Load("data/Press_A.png");
    CheckImages(Press_A, window, renderer);
    SDL_Texture *Press_ATexture = SDL_CreateTextureFromSurface(renderer, Press_A);
    SDL_FreeSurface(Press_A);
    CheckTexture(Press_ATexture, window, renderer);
    SDL_Rect Press_ARect = { (SCREEN_W - Press_A->w) / 2, (SCREEN_H - Press_A->h - 10), Press_A->w, Press_A->h };

    // Charger Author
    SDL_Surface *author = IMG_Load("data/author.png");
    CheckImages(author, window, renderer);
    SDL_Texture *authorTexture = SDL_CreateTextureFromSurface(renderer, author);
    SDL_FreeSurface(author);
    CheckTexture(authorTexture, window, renderer);
    SDL_Rect authorRect = { (SCREEN_W - author->w - 10), (SCREEN_H - author->h - 10), author->w, author->h };

    Mix_Chunk* Title = Mix_LoadWAV("data/sound/Title.wav");
    CheckSound(Title, window);
    Mix_PlayChannel(-1, Title, -1);

    while (appletMainLoop()) {

        // Mettre à jour les états des pads
        padUpdate(&pad);

        // Vérifier le bouton + pour quitter
        u32 kDown = padGetButtonsDown(&pad);
        if (kDown & HidNpadButton_Plus) {
            *continuer = false;
            break;
        }
        if (kDown & HidNpadButton_A) {
            Mix_HaltMusic();
            Mix_FreeChunk(Title);
            Play_A_MAIN(window);
            if (MainBackgroundTexture) SDL_DestroyTexture(MainBackgroundTexture);
            if (LogoTexture) SDL_DestroyTexture(LogoTexture);
            if (Press_ATexture) SDL_DestroyTexture(Press_ATexture);
            if (authorTexture) SDL_DestroyTexture(authorTexture);
            break;
        }
    
        // Déplacer le logo
        LogoAnimation(&LogoRect, &mov_logo);

        // Nettoyer l'écran
        SDL_RenderClear(renderer);

        // Afficher les textures
        SDL_RenderCopy(renderer, MainBackgroundTexture, NULL, &MainBackgroundRect);
        SDL_RenderCopy(renderer, LogoTexture, NULL, &LogoRect);
        SDL_RenderCopy(renderer, authorTexture, NULL, &authorRect);

        if (frame_count <= 30) {
            SDL_RenderCopy(renderer, Press_ATexture, NULL, &Press_ARect);
        } else if (frame_count >= 60) {
            frame_count = 0;
        }

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Attendre un peu
        SDL_Delay(16); // Environ 60 FPS

        frame_count += 1;
    }
}