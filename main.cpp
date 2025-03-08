#include "header/includeFile.h"

using namespace std; 

// định dạng cho hình vuông
void renderSquare(int x, int y, int size)
{
    SDL_Rect square;
    square.x = x;
    square.y = y;
    square.w = size;
    square.h = size;

    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &square);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}

bool isMouseInSquare(int x_mouse, int y_mouse, int x_square, int y_square, int size) {
    if ((x_mouse <= x_square+size and x_mouse >= x_square) and (y_mouse <= y_square+size and y_mouse >= y_square)) {
        return true;
    }
    return false;
}

bool isInRange (float range,Soldier soldier, int x_square, int y_square) {
    float dx = soldier.X - x_square;
    float dy = soldier.Y - y_square;
    float dis1 = sqrt(dx*dx + dy*dy) + square_size*sqrt(2);
    float dis2 = sqrt(dx*dx + dy*dy) - square_size*sqrt(2);

    if (dis1 <= range or dis2 <= range) {
        return true;
    }
    return false;
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
                        int mouseOption = 1;
                        while (inSetting) {
                            
                            KeyPress keyMenu = handleInput();
                            switch (keyMenu) {
                                case KEY_PRESS_UP:
                                    if (mouseOption > 0) mouseOption--;
                                    break;

                                case KEY_PRESS_DOWN:
                                    if (mouseOption < 3) mouseOption++;
                                    break;

                                
                                case KEY_PRESS_ENTER:
                                    switch (mouseOption) {
                                        case 0:
                                            setMouseSen(SLOW);
                                            inSetting = false;
                                            break;
                                        case 1:
                                            setMouseSen(NORMAL);
                                            inSetting = false;
                                            break;

                                        case 2:
                                            setMouseSen(FAST);
                                            inSetting = false;
                                            break;

                                        case 3:
                                            setMouseSen(SUPER_FAST);
                                            inSetting = false;
                                            break;
                                        default:
                                            break;

                                    }
                                    break;
                                
                                case KEY_PRESS_ESCAPE:
                                    inSetting = false;
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
            Soldier soldier = {1000, 1, SCREEN_W/2, SCREEN_H/2, 0, 0, 20};
            int dRange = 0;
            SDL_SetCursor(defaultCursor);
            while (gameStart){
                KeyPress pressInGame;
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if (e.button.button == SDL_BUTTON_LEFT) {
                            SDL_SetCursor(defaultCursor);
                            dRange = 0; 
                            if (isMouseInSquare(e.button.x, e.button.y, x_pos, y_pos, square_size)) {
                                if (isInRange(soldier.range, soldier, x_pos, y_pos)) {
                                    x_pos = rand() % (SCREEN_W - square_size);
                                    y_pos = rand () % (SCREEN_H - square_size);
                                }
                            }
                        } if (e.button.button == SDL_BUTTON_RIGHT) {
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
                renderSquare(x_pos, y_pos, square_size);
                drawPlayer(soldier);
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

// Nguyễn Minh Đức test update github