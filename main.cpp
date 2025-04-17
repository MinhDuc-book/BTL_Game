#include "header/includeFile.h"
#include <vector>

using namespace std; 

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
    SDL_DestroyTexture(idleOrcTexture);
    SDL_DestroyTexture(idleTexture);
    SDL_DestroyTexture(runOrcTexture);
    SDL_DestroyTexture(runTexture);
    SDL_DestroyTexture(attackOrcTexture);
    SDL_DestroyTexture(attackTexture);
    SDL_DestroyTexture(hurtOrcTexture);
    SDL_DestroyTexture(hurtTexture);

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
        
        TTF_Font *font  = TTF_OpenFont("data/PressStart2P-Regular.ttf", 30);
        Soldier soldier;
        Orc orc = {500, 1, 350, 274}; // health, level, X, Y, isRunning, isAttacking,isDeath, isHurt, direction, v_x, v_y, size, range
        vector <Orc> listOfOrcs;
        bool orcInit = false;

        soldier.size = 75;
        soldier.Health = 2500;
        soldier.Level = 1;

        soldier.X = SCREEN_W/2;
        soldier.Y = SCREEN_H/2;

        orc.size = 75;

        while (run) {
            KeyPress key = handleInput();
            switch(key) {
                case KEY_PRESS_UP:
                    if (option > 0) option --;
                    break;
                case KEY_PRESS_DOWN:
                    if (option < 4) option ++;
                    break;
                case KEY_PRESS_ENTER:
                    if (option == 0) {
                        gameStart = true;
                        run = false;
                    } else if (option == 1) {
                        restartGame(soldier, orc, Score);
                        gameStart = true;
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
                        
                    } else if (option == 3) {
                        bool inScore = true;
                        
                        while (inScore) {
                            KeyPress keyScore = handleInput();
                            if (keyScore == KEY_PRESS_ESCAPE) {
                                inScore = false;
                            }
                            SDL_RenderClear(gRenderer);
                            drawScoreOption(gRenderer, font);
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
            loadBackground(gRenderer, surfaceBackground, textureBackground, path_background);
            orc.flip = SDL_FLIP_NONE;

            if (!orcInit) {
                for (int i = 0; i < 2; ++i) {
                    Orc newOrc = {500, 1, createRandom(0,SCREEN_W), createRandom(50,SCREEN_H)};
                    newOrc.size = 75;
                    listOfOrcs.push_back(newOrc);
                }
                orcInit =true;
            }

            while (gameStart){
                soldier.isIdle = true;
                orc.isRunning = true;
                
                KeyPress pressInGame;
                
                int numberOfOrc = 1;

                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if (e.button.button == SDL_BUTTON_LEFT) {
                            
                            SDL_SetCursor(defaultCursor);
                            dRange = 0; 

                            //orc đơn
                            if (isMouseInSquare(e.button.x, e.button.y, orc)) {
                                if (isInRange( soldier, orc)) {
                                    orc.isDeath = true;
                                    if (soldier.X - orc.X <= 0) {
                                        soldier.flip = SDL_FLIP_NONE;
                                    } else if (soldier.X - orc.X > 0)  {
                                        soldier.flip = SDL_FLIP_HORIZONTAL;
                                    }

                                    // orc đơn
                                    int random_x = rand() % (SCREEN_W - orc.size);
                                    int random_y = 50 + rand () % (SCREEN_H - orc.size);
                                    orc.X = random_x;
                                    orc.Y = random_y;                           

                                    soldier.isAttacking = true;
                                    soldier.isRunning = false;
                                    soldier.isIdle = false;
                                    soldier.v = soldier.v + 0.00001f;

                                    soldier.Level = soldier.Level + 0.2f;
                                    cout << "isAttack: " << soldier.isAttacking << endl;
                                    cout << "isRunning: " << soldier.isRunning << endl;
                                    cout << "isIdle: " << soldier.isIdle << endl;

                                    orc.v = orc.v + 0.005f;
                                    Score = Score + 10;
                                }
                            }

                            // orc vector
                            for (int i = 0; i < listOfOrcs.size(); ++i) {
                                if (isMouseInSquare(e.button.x, e.button.y, listOfOrcs[i])) {
                                    if (isInRange(soldier, listOfOrcs[i])) {
                                        listOfOrcs[i].isDeath = true;
                                        // Respawn orc
                                        listOfOrcs[i].X = rand() % (SCREEN_W - listOfOrcs[i].size);
                                        listOfOrcs[i].Y = rand() % (SCREEN_H - listOfOrcs[i].size);
                            
                                        // Soldier actions
                                        soldier.isAttacking = true;
                                        soldier.v += 0.00001f;
                                        soldier.Level += 0.2f;
                                        Score += 10;
                                    }
                                }
                            }
                            
                            
                        } 
                        
                        if (e.button.button == SDL_BUTTON_RIGHT) {
                            if (soldier.isAttacking) {
                                soldier.isRunning = false;
                            } else {
                                soldier.isRunning = true;
                            }
                            x_end = e.button.x;
                            y_end = e.button.y;
                            if (x_end - soldier.X >= 0) {
                                soldier.flip = SDL_FLIP_NONE;
                            } else {
                                soldier.flip = SDL_FLIP_HORIZONTAL;
                            }

                            
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

                    if (soldier.Health <= 0) {
                        saveScore(Score, path_score);
                    }
                }
               
                movePlayer(soldier, x_end, y_end, soldier.v);

                SDL_RenderClear(gRenderer);

                drawBackground(gRenderer, textureBackground);

                if(dRange){
                    drawRange(soldier);
                }

                //
                if (x_end == soldier.X and y_end == soldier.Y) {
                    soldier.isRunning = false;
                    soldier.isIdle = true; 
                } else {
                    soldier.isRunning = true;
                }
                
                //
                if (isInRangeOrc(soldier, orc)) {
                    orc.isAttacking = true;
                    soldier.isHurt = true;
                    
                } else {
                    soldier.isHurt = false;
                }

                //orc đơn
                if (orc.X != soldier.X or orc.Y != soldier.Y) {
                    if (orc.X - soldier.X > 0) {
                        orc.flip = SDL_FLIP_HORIZONTAL;
                    } else {
                        orc.flip = SDL_FLIP_NONE;
                    }
                    moveOrc(orc, soldier, orc.v);
                }

                //orc vector
                for (auto &orc : listOfOrcs) {
                    if (!orc.isDeath) {
                        if (orc.X != soldier.X || orc.Y != soldier.Y) {
                            orc.flip = (orc.X - soldier.X > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
                            moveOrc(orc, soldier, orc.v);
                        }
                
                        if (isInRangeOrc(soldier, orc)) {
                            orc.isAttacking = true;
                            soldier.isHurt = true;
                        }
                    }
                }
                

                //
                if (soldier.Health <= 0) {
                    soldier.isDeath = true;
                    soldier.isHurt = false;
                    soldier.isIdle = false;
                    soldier.isAttacking = false;
                    soldier.isRunning = false; 

                    orc.isAttacking = false;
                    orc.isIdle = true;
                    orc.isRunning = false;
                    
                } else {
                    soldier.isDeath = false;
                }

                // orc đơn
                animationSoldier(soldier, orc);

                //orc vector
                for (int i = 0; i < 2; ++i) {
                    animationSoldier(soldier, listOfOrcs[i]);
                }

                // orc đơn
                animationOrc(orc,soldier);

                //orc vector
                for (int i = 0; i < 2; ++i) {
                    animationOrc(listOfOrcs[i], soldier);
                }

                //orc vector
                for (auto &orc : listOfOrcs) {
                    if (!orc.isDeath) {
                        animationOrc(orc, soldier);
                    }
                }
                
                
                getScore(Score, gRenderer, font);

                drawHealthBar(soldier, orc, gRenderer);

                if (soldier.isDeath) {
                    SDL_RenderClear(gRenderer);
                    GameOver(font, gRenderer, game_over);
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