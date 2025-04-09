#ifndef DRAW_FUNCTION_H
#define DRAW_FUNCTION_H

#include "commonVar.h"
#include "Object.h"
#include "ReactFunc.h"

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

void drawBackground(SDL_Renderer *renderer, const char *path) {
    SDL_Rect srcRect = {0, 0, 512,512};
    SDL_Rect desRect = {0, 0, 1000, 1000};

    SDL_Surface *background = IMG_Load(path);
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
    SDL_FreeSurface(background);

    SDL_RenderCopy(renderer,backgroundTexture,&srcRect, &desRect);
}



void drawMouseSettingMenu(SDL_Renderer* renderer, TTF_Font* font, int mouseOption) {
    SDL_Color White = {255, 255, 255};
    SDL_Color Red = {255, 0, 0};
    
    const char* options[] = {
        "Default Image",
        "Alt Image",
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

void drawIdle(SDL_Texture *texture, Soldier& soldier, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = soldier.X - soldier.size*2; 
    desRect.y = soldier.Y - soldier.size*2;
    desRect.w = soldier.size * 4;
    desRect.h = soldier.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (soldier.isIdle) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - soldier.lastFrameTime >= soldier.frameDelay) {
            soldier.currentFrame++;
            soldier.lastFrameTime = currentTime;

            if (soldier.currentFrame >= 6) { 
                soldier.currentFrame = 0;
                soldier.isIdle = false; 
            }
        }
        srcRect.x = soldier.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}

void drawHurting(SDL_Texture *texture, Soldier& soldier, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = soldier.X - soldier.size*2; 
    desRect.y = soldier.Y - soldier.size*2;
    desRect.w = soldier.size * 4;
    desRect.h = soldier.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (soldier.isHurt) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - soldier.lastFrameTime >= soldier.frameDelay) {
            soldier.currentFrame++;
            soldier.lastFrameTime = currentTime;

            if (soldier.currentFrame >= 4) { 
                soldier.currentFrame = 0;
                soldier.isHurt = false;
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

void drawOrcIdle(SDL_Texture *texture, Orc &orc, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = orc.X - orc.size*2; 
    desRect.y = orc.Y - orc.size*2;
    desRect.w = orc.size * 4;
    desRect.h = orc.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (orc.isIdle) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - orc.lastFrameTime >= orc.frameDelay) {
            orc.currentFrame++;
            orc.lastFrameTime = currentTime;

            if (orc.currentFrame >= 6) { 
                orc.currentFrame = 0;
                orc.isIdle = false; 
            }
        }
        srcRect.x = orc.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}

void drawOrcAttacking(SDL_Texture *texture, Orc &orc, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = orc.X - orc.size*2; 
    desRect.y = orc.Y - orc.size*2;
    desRect.w = orc.size * 4;
    desRect.h = orc.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (orc.isAttacking) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - orc.lastFrameTime >= orc.frameDelay) {
            orc.currentFrame++;
            orc.lastFrameTime = currentTime;

            if (orc.currentFrame >= 9) { 
                orc.currentFrame = 0;
                orc.isAttacking = false; 
            }
        }
        srcRect.x = orc.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}

void drawOrcRunning(SDL_Texture *texture, Orc &orc, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = orc.X - orc.size*2; 
    desRect.y = orc.Y - orc.size*2;
    desRect.w = orc.size * 4;
    desRect.h = orc.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (orc.isRunning) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - orc.lastFrameTime >= orc.frameDelay) {
            orc.currentFrame++;
            orc.lastFrameTime = currentTime;

            if (orc.currentFrame >= 8) { 
                orc.currentFrame = 0;
                orc.isAttacking = false; 
            }
        }
        srcRect.x = orc.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}

void animationOrc (Orc &orc) {
    if (orc.isRunning) {
        runOrcTexture = SDL_CreateTextureFromSurface(gRenderer, spriteOrcRun);
        currentOrcTexture = runOrcTexture;
        drawOrcRunning(currentOrcTexture, orc, gRenderer);
    }
    else if(orc.isIdle) {
        idleOrcTexture = SDL_CreateTextureFromSurface(gRenderer, spriteOrcIdle);
        orc.isRunning = false;
        currentOrcTexture = idleOrcTexture;
        drawOrcIdle(currentOrcTexture, orc, gRenderer);
    }
    else if (orc.isAttacking) {
        attackOrcTexture = SDL_CreateTextureFromSurface(gRenderer, spriteOrcAttack);
        orc.isRunning = false;
        currentOrcTexture = attackOrcTexture;
        drawOrcAttacking(currentOrcTexture, orc, gRenderer);
    }
}

void animationSoldier(Soldier &soldier) {
    if (soldier.isAttacking) {
        attackTexture = SDL_CreateTextureFromSurface(gRenderer, spriteAttack);
        soldier.isIdle = false;
        currentTexture = attackTexture;
        drawAttacking(currentTexture, soldier, gRenderer);
    }
    else if (soldier.isRunning) {
        runTexture = SDL_CreateTextureFromSurface(gRenderer, spriteRun);
        soldier.isIdle = false;
        currentTexture = runTexture;
        drawRunning(currentTexture,soldier,gRenderer);
    }
    else if (soldier.isIdle) {
        idleTexture = SDL_CreateTextureFromSurface(gRenderer, spriteIdle);
        currentTexture = idleTexture;
        drawIdle(currentTexture, soldier, gRenderer);
    }
    else if (soldier.isHurt) {
        hurtTexture = SDL_CreateTextureFromSurface(gRenderer, spriteHurt);
        soldier.isAttacking = false;
        soldier.isRunning = false;
        soldier.isIdle = false;
        currentTexture = hurtTexture;
        drawHurting(currentTexture, soldier, gRenderer);
    }
}


#endif