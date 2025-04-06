#include "header/includeFile.h"

using namespace std; 

bool isMouseInSquare(int x, int y, Orc orc) {
    if (x <= orc.size + orc.X and x >= orc.X - orc.size and y <= orc.Y + orc.size and y >= orc.Y - orc.size) {
        return true;
    }
    return false;
}

bool isInRange(Soldier soldier, Orc orc) {
    float dx = soldier.X - orc.X;
    float dy = soldier.Y - orc.Y;
    float distance = sqrt(dx*dx + dy*dy) - orc.size;
    return distance <= soldier.range;
}

SDL_Event e;

// xử lí phím nhấn (hàm xử lí sự kiện)
KeyPress handleInput() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == QUIT) {
            currentState = QUIT;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                return KEY_PRESS_UP;
                break;

                case SDLK_DOWN:
                return KEY_PRESS_DOWN;
                break;

                case SDLK_ESCAPE:
                currentState = QUIT;
                return KEY_PRESS_ESCAPE;
                break;
                
                case SDLK_RETURN:
                return KEY_PRESS_ENTER;
                break; 
                
                default:
                break;
            }
        }
        
    }
    return KEY_PRESS_DEFAULT;
}


// đóng cửa sổ, giải phóng bộ nhớ
void close() 
{
    SDL_FreeCursor(attackCursor);
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main (int argv, char *argc[]) {
    if (init() == false) {
        cout << "Cannot initialized window" << endl;
    }  else {
        
        TTF_Font *font  = TTF_OpenFont("data/JetBrainsMono-Regular.ttf", 50);

        Soldier soldier;
        soldier.size = 75;
        soldier.X = SCREEN_W/2;
        soldier.Y = SCREEN_H/2;

        Orc orc = {500, 1, 350, 274}; // health, level, X, Y, isRunning, isAttacking,isDeath, isHurt, direction, v_x, v_y, size, range
        orc.size = 50;

        while (run) {
            KeyPress key = handleInput();
            switch(key) {
                case KEY_PRESS_UP:
                    if (option > 0) option --;
                    break;
                case KEY_PRESS_DOWN:
                    if (option < 3) option ++;
                    break;
                case KEY_PRESS_ENTER:
                    if (option == 0) {
                        gameStart = true;
                        run = false;
                    } else if (option == 1) {
                        cout << "Comming soon" << endl;
                    } else if (option == 2) {
                        // MOUSE SETTING
                        bool inSetting = true;
                        while (inSetting) {
                            KeyPress keyMouseoption = handleInput();
                            switch (keyMouseoption) {
                                case KEY_PRESS_UP:
                                    if (mouseOption > 0) mouseOption--;
                                    break;

                                case KEY_PRESS_DOWN:
                                    if (mouseOption < 2) mouseOption++;
                                    break;

                                case KEY_PRESS_ENTER:
                                    switch(mouseOption) {
                                        case 0:
                                            defaultCursor = saveDefaultCursor;
                                            SDL_SetCursor(defaultCursor);
                                            inSetting = false;
                                            break;
                                        case 1:
                                            defaultCursor = altCursor;
                                            SDL_SetCursor(defaultCursor);
                                            inSetting = false;
                                            break;

                                        case 2:
                                            defaultCursor = handWritingCursor;
                                            SDL_SetCursor(defaultCursor);
                                            inSetting = false;
                                            break;

                                        
                                    }
                                    break;
                                case KEY_PRESS_ESCAPE:
                                    inSetting = false;
                                    break;
                                default:
                                    break;     
                            }

                            SDL_RenderClear(gRenderer);
                            drawMouseSettingMenu(gRenderer, font, mouseOption);
                            SDL_RenderPresent(gRenderer);
                        }
                        
                    } else {
                        run = false;
                    }
                    break;
                case KEY_PRESS_ESCAPE:
                    run = false;
                    break;
                default:
                    break;
                
            }
            int dRange = 0;
            SDL_SetCursor(defaultCursor);
            while (gameStart){

                KeyPress pressInGame;
                while (SDL_PollEvent(&e) != 0) {

                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if (e.button.button == SDL_BUTTON_LEFT) {
                            SDL_SetCursor(defaultCursor);
                            dRange = 0; 
                            if (isMouseInSquare(e.button.x, e.button.y, orc)) {
                                if (isInRange( soldier, orc)) {
                                    int random_x = rand() % (SCREEN_W - orc.size);
                                    int random_y = rand () % (SCREEN_H - orc.size);
                                    orc.X = random_x;
                                    orc.Y = random_y;
                                    soldier.isAttacking = true;

                                }
                            }
                        } 
                        
                        if (e.button.button == SDL_BUTTON_RIGHT) {
                            x_end = e.button.x;
                            y_end = e.button.y;
                            v = 5;
                        }
                    }

                    if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_ESCAPE) {
                            run = true;
                            gameStart = false;
                        }
                        if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_TAB) {
                            dRange++;
                            dRange %= 2;
                            SDL_SetCursor(attackCursor);
                        }
                    } 
                }
                movePlayer(soldier, x_end, y_end, v);
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                SDL_RenderClear(gRenderer);
                if(dRange){
                    drawRange(soldier);
                }
                drawOrc(orc);
                drawPlayer(soldier);
                if (soldier.isAttacking) {
                    attackTexture = SDL_CreateTextureFromSurface(gRenderer, spriteAttack);
                    currentTexture = attackTexture;
                    drawAttacking(currentTexture, soldier, gRenderer);
                }
                
                SDL_RenderPresent(gRenderer);
            }
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            SDL_RenderClear(gRenderer);
            drawMenu(gRenderer, font, option);
        }
    }
    
    close();
    return 0;
}

// Nguyễn Minh Đức 