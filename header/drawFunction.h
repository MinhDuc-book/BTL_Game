#ifndef DRAW_FUNCTION_H
#define DRAW_FUNCTION_H

#include "commonVar.h"
#include "Object.h"

// draw menu
void drawMenu(SDL_Renderer *menuRenderer, TTF_Font *font, int selecOption ){
    const char *Menu[STATE_TOTAL] = {"Start", "High Score", "Setting", "Quit"};

    SDL_Color red = {255, 0, 0};
    SDL_Color white = {255, 255, 255};

    for (int i = 0; i < 4; i++) {
        // create color for selection
        SDL_Surface *menuSurface = TTF_RenderUTF8_Solid(font, Menu[i], (i == selecOption) ? red : white);
        SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(menuRenderer, menuSurface);

        // size of text
        int menuHigh = menuSurface -> h;
        int menuWidth = menuSurface -> w;

        // no longer use
        SDL_FreeSurface (menuSurface);

        // region to draw
        SDL_Rect menuRect = {SCREEN_W/2 - 100, SCREEN_H/2 - 100 + menuHigh * i, menuWidth, menuHigh };
        SDL_RenderCopy(menuRenderer, menuTexture, NULL, &menuRect);
        SDL_DestroyTexture(menuTexture);
    }
    SDL_RenderPresent(menuRenderer);
}


void drawMouseSettingMenu(SDL_Renderer* renderer, TTF_Font* font, int mouseOption) {
    SDL_Color White = {255, 255, 255};
    SDL_Color Red = {255, 0, 0};
    
    const char* options[] = {
        "Default Image",
        "ALT Image",
        "Handwriting Image"  
    };
    
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "===Mouse Option===", White);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Rect titleRect = {SCREEN_W/2 - 150, SCREEN_H/2 - 200, 300, 50};
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);
    
    for(int i = 0; i < 3; i++) {
        SDL_Color color = (i == mouseOption) ? Red : White;
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, options[i], color);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        
        SDL_Rect Message_rect;
        Message_rect.x = SCREEN_W/2 - 100;
        Message_rect.y = SCREEN_H/2 - 100 + i*80;  
        Message_rect.w = 300;
        Message_rect.h = 80;
        
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);
    }
}


// vẽ tầm đánh
void drawRange(Soldier soldier)
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    for (float i = 0; i <= 360; i = i+0.1) {
        SDL_RenderDrawPoint(gRenderer,soldier.X + soldier.range*cos(i*180/PI), soldier.Y + soldier.range*sin(i*180/PI));
    }
}

void loadSoldier(SDL_Renderer *renderer, const char *path, SDL_Rect desRect, SDL_Rect srcRect, double angle) {
    SDL_Surface *loadedSurface = IMG_Load(path);
    gTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    SDL_RenderCopyEx(renderer, gTexture, &srcRect, &desRect, angle, nullptr, SDL_FLIP_NONE);
}

// draw character
void drawPlayer(Soldier soldier){
    SDL_Rect desRect;
    desRect.x = soldier.X - 25;
    desRect.y = soldier.Y - 25;
    desRect.w = 50;  
    desRect.h = 50;

    SDL_Rect srcRect;
    srcRect.x = 0;  
    srcRect.y = 0;
    srcRect.w = 50;
    srcRect.h = 50;

    //lồng if vào đây để tạo các chuyển động cho nhân vật
    loadSoldier(gRenderer, path_soldier_idle, desRect, srcRect, 0.0);

    switch (soldier.state) {
        case IDLE:
            srcRect.x = currentFrame * srcRect.w; 
            loadSoldier(gRenderer, path_soldier_idle, desRect, srcRect, 0.0);
            break;
        case ATTACK:
            srcRect.x = currentFrame * srcRect.w; 
            loadSoldier(gRenderer, path_soldier_attack, desRect, srcRect, 0.0);
            break;
        case RUN:
            srcRect.x = currentFrame * srcRect.w; 
            loadSoldier(gRenderer, path_soldier_run, desRect, srcRect, 0.0);
            break;
        case DEATH:
            srcRect.x = currentFrame * srcRect.w; 
            loadSoldier(gRenderer, path_soldier_death, desRect, srcRect, 0.0);
            break;
        case HURT:
            srcRect.x = currentFrame * srcRect.w; 
            loadSoldier(gRenderer, path_soldier_hurt, desRect, srcRect, 0.0);
            break;
        default:
            break;
    }
}

void loadOrc (SDL_Renderer *renderer, const char *path, SDL_Rect desRect, SDL_Rect srcRect, double angle) {
    SDL_Surface *loadedSurface = IMG_Load(path);
    gTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface (loadedSurface);
    SDL_RenderCopyEx(renderer, gTexture, &srcRect, &desRect, angle, nullptr, SDL_FLIP_NONE);
}
void drawOrc (Orc orc) {
    SDL_Rect desRect;
    desRect.x = orc.X - orc.size;
    desRect.y = orc.Y - orc.size;
    desRect.w = 50;
    desRect.h = 50;

    SDL_Rect srcRect;
    srcRect.x = 0;  
    srcRect.y = 0;
    srcRect.w = 50;
    srcRect.h = 50;

    loadOrc (gRenderer, path_orc_idle, desRect, srcRect, 0.0);
}


#endif