#ifndef REACT_FUNCTION_H
#define REACT_FUNCTION_H

#include "includeFile.h"
#include "Object.h"
#include "commonVar.h"
#include <string>
#include <iomanip>
#include <sstream>

void movePlayer(Soldier &soldier, int x_mouse, int y_mouse, float v) {
    float dx = x_mouse - soldier.X;
    float dy = y_mouse - soldier.Y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > v) {
        float stepX = v * (dx / distance);
        float stepY = v * (dy / distance);

        soldier.X += stepX;
        soldier.Y += stepY;
    } else if (distance > 0) {
        soldier.X = x_mouse;
        soldier.Y = y_mouse;
    }
    
}

void drawAttacking(SDL_Texture *texture, Soldier soldier, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = soldier.X;
    desRect.y = soldier.Y;
    desRect.w = soldier.size;
    desRect.h = soldier.size;

    srcRect.w = soldier.size;
    srcRect.h = soldier.size;
    srcRect.y = 0; 

    if (soldier.isAttacking) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - soldier.lastFrameTime >= soldier.frameDelay) {
            soldier.currentFrame++;
            soldier.lastFrameTime = currentTime;
    
            if (soldier.currentFrame >= 6) {
                soldier.currentFrame = 0;
                soldier.isAttacking = false; // Kết thúc animation
            }
        }
        srcRect.x = soldier.currentFrame * soldier.size; 
    }
    
    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}


#endif