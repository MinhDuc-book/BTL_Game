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
        soldier.isIdle = true;
    }
    
}

void moveOrc(Orc &orc, Soldier soldier, float v) {
    float dx = soldier.X - orc.X;
    float dy = soldier.Y - orc.Y;
    float distance = sqrt (dx * dx + dy * dy);

    if (distance > v/2) {
        float stepX = v * (dx/distance > 0 ? 1 : -1);
        float stepY = v * (dy/distance > 0 ? 1 : -1);

        orc.X += stepX;
        orc.Y += stepY;
        
    } else if (distance > 0) {
        orc.X = soldier.X;
        orc.Y = soldier.Y;
        
    }
}

void drawAttacking(SDL_Texture *texture, Soldier& soldier, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = soldier.X - soldier.size*2; 
    desRect.y = soldier.Y - soldier.size*2;
    desRect.w = soldier.size * 4;
    desRect.h = soldier.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (soldier.isAttacking) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - soldier.lastFrameTime >= soldier.frameDelay) {
            soldier.currentFrame++;
            soldier.lastFrameTime = currentTime;

            if (soldier.currentFrame >= 9) { 
                soldier.currentFrame = 0;
                soldier.isAttacking = false; 
            }
        }
        srcRect.x = soldier.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}

void drawRunning(SDL_Texture *texture, Soldier& soldier, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = soldier.X - soldier.size*2; 
    desRect.y = soldier.Y - soldier.size*2;
    desRect.w = soldier.size * 4;
    desRect.h = soldier.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (soldier.isRunning) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - soldier.lastFrameTime >= soldier.frameDelay) {
            soldier.currentFrame++;
            soldier.lastFrameTime = currentTime;

            if (soldier.currentFrame >= 8) { 
                soldier.currentFrame = 0;
                soldier.isAttacking = false; 
            }
        }
        srcRect.x = soldier.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}


#endif