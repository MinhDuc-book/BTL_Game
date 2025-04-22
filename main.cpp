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
        vector <Orc> listOfOrcs;
        bool orcInit = false;

        soldier.size = 75;
        soldier.Health = 7500;
        soldier.Level = 1;
        soldier.X = SCREEN_W/2;
        soldier.Y = SCREEN_H/2;

        vector <Arrow> arrows;

        loadBackground(gRenderer, surfaceBackground, textureBackground, path_background);
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
                        restartGame(soldier, Score);
                        gameStart = true;
                    } else if (option == 2) {
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
            
            int numberOfOrc = 4;
            if (!orcInit) {
                for (int i = 0; i < numberOfOrc; ++i) {
                    Orc newOrc = {500, 1, createRandom(0,SCREEN_W), createRandom(50,SCREEN_H)};
                    newOrc.size = 75;
                    newOrc.flip = SDL_FLIP_NONE;
                    newOrc.isRunning = true;
                    listOfOrcs.push_back(newOrc);
                }
                orcInit = true;
            }

            while (gameStart){
                soldier.isIdle = true;
                KeyPress pressInGame;
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if (e.button.button == SDL_BUTTON_LEFT) {
                            
                            SDL_SetCursor(defaultCursor);
                            dRange = 0; 

                            for (int i = 0; i < numberOfOrc; ++i) {

                                if (isMouseInSquare(e.button.x, e.button.y, listOfOrcs[i])) {
                                    if (isInRange(soldier, listOfOrcs[i])) {
                                        Arrow newArrow(soldier.X, soldier.Y, listOfOrcs[i].X, listOfOrcs[i].Y, 5.0f);
                                        arrows.push_back(newArrow);
                                        soldier.isAttacking = true;

                                        if (soldier.doneAttack) {
                                            listOfOrcs[i].X = rand() % (SCREEN_W - listOfOrcs[i].size);
                                            listOfOrcs[i].Y = 50 + rand() % (SCREEN_H - listOfOrcs[i].size - 20);
                                            Score += 5;
                                            soldier.Level += 0.2f;
                                            soldier.v += 0.00001f;
                                        }
                                  
                                        
                                    }
                                }

                                

                            }
                        }

                        
                        
                        if (e.button.button == SDL_BUTTON_RIGHT) {
                            if (soldier.isAttacking) {
                                soldier.isRunning = false;
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
                for (auto &orc : listOfOrcs) {
                    if (isInRangeOrc(soldier, orc)) {
                        orc.isAttacking = true;
                        soldier.isHurt = true;
                        
                    } else {
                        soldier.isHurt = false;
                    }
                }


                //orc vector
                for (auto &orc : listOfOrcs) {

                    if (orc.X != soldier.X || orc.Y != soldier.Y) {
                        orc.flip = (orc.X - soldier.X > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
                        moveOrc(orc, soldier, orc.v);
                    }
            
                    if (isInRangeOrc(soldier, orc)) {
                        orc.isAttacking = true;
                        orc.isRunning = false;
                        orc.isIdle = false;
                        soldier.isHurt = true;
                        soldier.Health = soldier.Health - 10;
                    } else {
                        orc.isAttacking = false;
                        orc.isRunning = true;
                        orc.isIdle = false;
                    }
                        
                    
                }
                
                //orc vector
                for (auto &orc : listOfOrcs) {
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
                }

                animationSoldier(soldier);
                

                //orc vector
                for (auto &orc : listOfOrcs) {
                    drawHealthOrc(orc, gRenderer);
                    animationOrc(orc, soldier);
                }

                
                
                getScore(Score, gRenderer, font);

                drawHealthBar(soldier, gRenderer);

                if (soldier.isDeath) {
                    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                    SDL_RenderClear(gRenderer);
                    GameOver(font, gRenderer, game_over);
                    
                }
                
                    
                for (auto &arrow : arrows) {
                        arrow.moveArrow();
                        arrow.renderArrow(gRenderer);
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
// tách riêng từng loại animation rồi đưa vào logic hợp lí chứ không gộp chung nữa