#ifndef DRAW_FUNCTION_H
#define DRAW_FUNCTION_H

#include "commonVar.h"
#include "Object.h"
#include "ReactFunc.h"
#include <string>
#include <cmath> 
#include <cstring>

// draw menu
void drawMenu(SDL_Renderer *menuRenderer, TTF_Font *font, int selecOption ){
    const char *Menu[STATE_TOTAL] = {"Start", "Restart", "Setting", "Score", "Quit"};

    SDL_Color red = {255, 0, 0};
    SDL_Color white = {255, 255, 255};

    for (int i = 0; i < 5; i++) {
        SDL_Surface *menuSurface = TTF_RenderUTF8_Solid(font, Menu[i], (i == selecOption) ? red : white);
        SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(menuRenderer, menuSurface);

        int menuHigh = menuSurface -> h;
        int menuWidth = menuSurface -> w;

        SDL_FreeSurface (menuSurface);

        SDL_Rect menuRect = {SCREEN_W/2 - 100, SCREEN_H/2 - 100 + (menuHigh+30) * (i), menuWidth, menuHigh };
        SDL_RenderCopy(menuRenderer, menuTexture, NULL, &menuRect);
        SDL_DestroyTexture(menuTexture);
    }
    SDL_RenderPresent(menuRenderer);
}

void loadBackground(SDL_Renderer *renderer, SDL_Surface * &surface,SDL_Texture * &texture, const char *path) {
    surface = IMG_Load(path);
    if (surface == NULL) {
        cout << "Cannot load image" << endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void drawBackground(SDL_Renderer* renderer, SDL_Texture* loadTexture) {
    SDL_Rect desRect;
    SDL_Rect srcRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = 1024;
    srcRect.w = 1536;

    desRect.x = 0;
    desRect.y = 0;
    desRect.h = SCREEN_H;
    desRect.w = SCREEN_W;
    SDL_RenderCopyEx(renderer, loadTexture, &srcRect, &desRect, 0, nullptr, SDL_FLIP_NONE);
    
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

void drawBlindBox(SDL_Renderer *renderer) {
    blindBoxTexture = SDL_CreateTextureFromSurface(renderer, blindBoxSurface);
    SDL_Rect srcRect = {0, 0, 1024, 1024};
    SDL_Rect desRect = {createRandom(0,SCREEN_W), createRandom(50,SCREEN_H), 50, 50};
}

void drawScoreOption(SDL_Renderer *renderer, TTF_Font *font) {
    const char *string_highest = to_string(findHighestScore(path_score)).c_str();
    const char *string_lowest = to_string(findLowestScore(path_score)).c_str();
    const char *string_average = to_string(findAverageScore(path_score)).c_str();
    SDL_Color cream = {240, 240, 220};

    const char *aboutScore[] = {
        "Lowest Score: ",
        "Highest Score: ",
        "Average Score: "
    };

    const char *Score[] = {
        string_lowest,
        string_highest,
        string_average
    };

    SDL_Surface *title = TTF_RenderText_Solid(font, "===Score===", cream);
    SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, title);
    SDL_Rect titleRect = {SCREEN_W/2 - 150, SCREEN_H/2 - 200, 300, 50};
    SDL_RenderCopy(renderer, titleTexture,NULL, &titleRect);

    SDL_FreeSurface(title);
    SDL_DestroyTexture(titleTexture);

    for (int i = 0; i < 3; ++i) {
        SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, aboutScore[i], cream);
        SDL_Texture *textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect rectMessage = {SCREEN_W/2 - 200, SCREEN_H/2 - 100 + i*80, 300, 50};

        SDL_Surface *surfaceScore = TTF_RenderText_Solid(font, Score[i], cream);
        SDL_Texture *textureScore = SDL_CreateTextureFromSurface(renderer, surfaceScore);
        SDL_Rect rectScore = {SCREEN_W/2 + 150, SCREEN_H/2 - 100 + i*80, 50, 50};

        SDL_RenderCopy(renderer, textureScore, NULL, &rectScore);
        SDL_FreeSurface(surfaceScore);
        SDL_DestroyTexture(textureScore);

        SDL_RenderCopy(renderer, textureMessage, NULL, &rectMessage);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(textureMessage);
    }
}

void drawHealthBar (Soldier &soldier, SDL_Renderer *renderer) {
    SDL_Rect srcRect = {0, 0, 1024, 1024};
    SDL_Rect desRect = {1, 1, 240, 50};
    healthBarTexture = SDL_CreateTextureFromSurface(renderer, healthBarSurface);
    SDL_RenderCopy(renderer, healthBarTexture, &srcRect, &desRect);

    SDL_Color red = {168, 0, 0};
    SDL_Rect healthBar = {21, 20, (soldier.Health / 36 - 5) >= 0 ? (soldier.Health / 36 - 5) * 1 : 0, 15};
    SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, 255);
    SDL_RenderFillRect(renderer, &healthBar);
    
}

void drawHealthOrc(Orc &orc, SDL_Renderer *renderer) {
    SDL_Color red = {168, 0, 0};
    SDL_Rect healthOrcBar = {orc.X - orc.size/2 + 17, orc.Y - orc.size/2 + 5, 40, 5};
    SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, 255);
    SDL_RenderFillRect(renderer, &healthOrcBar);

}

void drawRange(Soldier soldier)
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    for (float i = 0; i <= 360; i = i+0.1) {
        SDL_RenderDrawPoint(gRenderer,soldier.X + soldier.range*cos(i*180/PI), soldier.Y + soldier.range*sin(i*180/PI));
    }
}

void drawLine(Soldier &soldier, Orc &orc, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, soldier.X, soldier.Y, orc.X, orc.Y);
    SDL_RenderPresent(renderer);
} 

void getScore(int score, SDL_Renderer *renderer, TTF_Font *font) {
    string scoreText = "SCORE: " + to_string(score);
    SDL_Color cream = {240, 240, 220};

    scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), cream);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_Rect whereScore = {SCREEN_W - 200, 1, 200,30};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &whereScore);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture); 
}

void GameOver(TTF_Font *font, SDL_Renderer *renderer, const char *path_game_over) {
    SDL_Color cream = {240, 240, 220};
    SDL_Color red = {255, 20, 20};
    gameOverSurface = TTF_RenderText_Solid(font, path_game_over, cream);
    gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    SDL_Rect gameOverPosition = {SCREEN_W / 2 - 300, SCREEN_H / 2 - 100, 600, 100};
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverPosition);
    SDL_FreeSurface(gameOverSurface);
    SDL_DestroyTexture(gameOverTexture);
}

/*
void drawSplitAttack (SDL_Texture *texture, Soldier &soldier, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = soldier.X - soldier.size*2; 
    desRect.y = soldier.Y - soldier.size*2;
    desRect.w = soldier.size * 7;
    desRect.h = soldier.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;


        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - soldier.lastFrameTime >= soldier.frameDelay) {
            soldier.currentFrame++;
            soldier.lastFrameTime = currentTime;
            if (soldier.currentFrame >= 6) { 
                soldier.currentFrame = 0;
                soldier.isAttacking = false;
            }
        }
        srcRect.x = soldier.currentFrame * 100;

    SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, 0, nullptr, soldier.flip);

}
*/

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

    soldier.doneAttack = false;
    if (soldier.doneAttack == false) {
        soldier.isRunning = false;
        soldier.isIdle = false;
    }
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - soldier.lastFrameTime >= soldier.frameDelay) {
        soldier.currentFrame++;
        soldier.lastFrameTime = currentTime;
        if (soldier.currentFrame >= 9) {
            soldier.doneAttack = true;
            soldier.isAttacking = false;
            soldier.currentFrame = 0;

        }
    }
    srcRect.x = soldier.currentFrame * 100;
    

    SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, 0, nullptr, soldier.flip);
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
                soldier.isRunning = false; 
            }
        }
        srcRect.x = soldier.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, 0, nullptr, soldier.flip);
}

void drawDeath (SDL_Texture *texture, Soldier &soldier, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = soldier.X - soldier.size*2; 
    desRect.y = soldier.Y - soldier.size*2;
    desRect.w = soldier.size * 4;
    desRect.h = soldier.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (soldier.isDeath) {
        soldier.frameDelay = 500;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - soldier.lastFrameTime >= soldier.frameDelay) {
            soldier.currentFrame++;
            soldier.lastFrameTime = currentTime;

            if (soldier.currentFrame >= 4) { 
                soldier.currentFrame = 0;
                soldier.isDeath = false; 
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

void drawOrcAttacking(SDL_Texture *texture, Orc &orc,Soldier soldier, SDL_Renderer *renderer) {
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

            if (orc.currentFrame >= 6) { 
                orc.currentFrame = 0;
                orc.isAttacking = false; 
                
            }
        }
        srcRect.x = orc.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, 0, nullptr, orc.flip);
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

    SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, 0, nullptr, orc.flip);
}

void drawOrcDeath(SDL_Texture *texture, Orc &orc, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    SDL_Rect desRect;

    desRect.x = orc.X - orc.size*2; 
    desRect.y = orc.Y - orc.size*2;
    desRect.w = orc.size * 4;
    desRect.h = orc.size * 4;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.y = 0;

    if (orc.isDeath) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - orc.lastFrameTime >= orc.frameDelay) {
            orc.currentFrame++;
            orc.lastFrameTime = currentTime;

            if (orc.currentFrame >= 4) { 
                orc.currentFrame = 0;
                orc.isDeath = false; 
            }
        }
        srcRect.x = orc.currentFrame * 100;
    } else {
        srcRect.x = 0;
    }

    SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, 0, nullptr, orc.flip);
}

void animationOrc (Orc &orc, Soldier soldier) {
    if (orc.isAttacking) {
        attackOrcTexture = SDL_CreateTextureFromSurface(gRenderer, spriteOrcAttack);
        currentOrcTexture = attackOrcTexture;
        drawOrcAttacking(currentOrcTexture, orc, soldier, gRenderer);
    }
    else if (orc.isRunning) {
        runOrcTexture = SDL_CreateTextureFromSurface(gRenderer, spriteOrcRun);
        currentOrcTexture = runOrcTexture;
        drawOrcRunning(currentOrcTexture, orc, gRenderer);
    }
    else if(orc.isIdle) {
        idleOrcTexture = SDL_CreateTextureFromSurface(gRenderer, spriteOrcIdle);
        currentOrcTexture = idleOrcTexture;
        drawOrcIdle(currentOrcTexture, orc, gRenderer);
    } else if (orc.isDeath) {
        deathOrcTexture = SDL_CreateTextureFromSurface(gRenderer, spriteOrcDeath);
        currentOrcTexture = deathOrcTexture;
        drawOrcDeath(currentOrcTexture, orc, gRenderer);
    }
    
}

void animationSoldier(Soldier &soldier) {
    if (soldier.isHurt) {
        hurtTexture = SDL_CreateTextureFromSurface(gRenderer, spriteHurt);
        currentTexture = hurtTexture;
        drawHurting(currentTexture, soldier, gRenderer);
    }
    else if (soldier.isAttacking) {
        attackTexture = SDL_CreateTextureFromSurface(gRenderer, spriteAttack);
        currentTexture = attackTexture;
        drawAttacking(currentTexture, soldier, gRenderer);
    }

    else if (soldier.isRunning) {
        runTexture = SDL_CreateTextureFromSurface(gRenderer, spriteRun);
        currentTexture = runTexture;
        drawRunning(currentTexture,soldier,gRenderer);
    }

    else if (soldier.isIdle) {
        idleTexture = SDL_CreateTextureFromSurface(gRenderer, spriteIdle);
        currentTexture = idleTexture;
        drawIdle(currentTexture,soldier,gRenderer);
    }
    
}

#endif