#ifndef DRAW_FUNCTION_H
#define DRAW_FUNCTION_H

#include "commonVar.h"
#include "Object.h"

// draw menu
void drawMenu(SDL_Renderer *menuRenderer, TTF_Font *font, int selecOption ){
    const char *Menu[STATE_TOTAL] = {"Start", "High Score", "Quit"};

    SDL_Color red = {255, 0, 0};
    SDL_Color blue = {0, 0 , 255};

    for (int i = 0; i < 3; i++) {
        // create color for selection
        SDL_Surface *menuSurface = TTF_RenderUTF8_Solid(font, Menu[i], (i == selecOption) ? red : blue);
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

// vẽ tầm đánh
void drawRange(Soldier soldier)
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    for (float i = 0; i <= 360; i = i+0.1) {
        SDL_RenderDrawPoint(gRenderer,soldier.X + soldier.range*cos(i*180/PI), soldier.Y + soldier.range*sin(i*180/PI));
    }
}

// draw character
void drawPlayer(Soldier soldier){
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    for (int i = -soldier.size; i <= soldier.size; i++){
        for (int j = -soldier.size; j <= soldier.size ; j++){
            if (sqrt(i*i + j*j) <= soldier.size){
                SDL_RenderDrawPoint(gRenderer, j + soldier.X, i + soldier.Y);
            }
        }
    }
}

#endif