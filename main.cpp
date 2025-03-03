#include "header/includeFile.h"

using namespace std;

// kiểm tra khởi tạo
bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initalized %s\n" << SDL_GetError() << endl;
        success = false;
    } else if (TTF_Init() < 0) {
        cout << "Cannot initialize TTF" << TTF_GetError() << endl;
        success = false;
    } else {
        gWindow = SDL_CreateWindow("AimGame", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_W,SCREEN_H,SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            cout << "Window could not initalized %s\n" << SDL_GetError() << endl;
            success = false;
        } else {
            // tạo renderer cho cửa sổ
            gRenderer = SDL_CreateRenderer(gWindow, - 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                cout << "Renderer could not created! SDL_ERROR:" << SDL_GetError() << endl;
                success = false;
            } else {
                // khởi tạo con trỏ chuột mới
                SDL_Surface *attackPointer = IMG_Load ("Icon/Ping_Target.png");
                SDL_Surface *defaultPointer = IMG_Load ("Icon/defaultCursor.png");
                if (attackPointer == NULL) {
                    cout << "Failed to load image" << IMG_GetError() << endl;
                    success = false;
                } else {
                    attackCursor = SDL_CreateColorCursor(attackPointer, attackPointer->w / 2, attackPointer->h /2);
                    defaultCursor = SDL_CreateColorCursor(defaultPointer, 0, 0);
                    if (attackCursor == nullptr) {
                        cout << "Failed to load cursor" << SDL_GetError() << endl;
                        success = false;
                    }
                    SDL_FreeSurface(attackPointer);
                    SDL_FreeSurface(defaultPointer);
                    attackPointer = nullptr;
                    defaultPointer = nullptr;
                };
            }
        }
    }

    return success;
}  

// định dạng cho hình vuông
void renderSquare(int x, int y, int size)
{
    SDL_Rect square;
    square.x = x;
    square.y = y;
    square.w = size;
    square.h = size;

    // đặt màu cho renderer (chọn màu bút)
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);

    // vẽ hình từ renderer lên square (to màu)
    SDL_RenderFillRect(gRenderer, &square);

    // định nghĩa màu nền trước khi clear để tránh bị nhầm nền
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}

bool isMouseInSquare(int x_mouse, int y_mouse, int x_square, int y_square, int size) {
    if ((x_mouse <= x_square+size and x_mouse >= x_square) and (y_mouse <= y_square+size and y_mouse >= y_square)) {
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
                    if (option < 2) option ++;
                    break;
                case KEY_PRESS_ENTER:
                    if (option == 0) {
                        gameStart = true;
                        run = false;
                    } else if (option == 1) {
                        cout << "Comming soon" << endl;
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

            SDL_SetCursor(defaultCursor);
            while (gameStart){
                KeyPress pressInGame;
                SDL_GetMouseState(&x_mouse, &y_mouse);
                
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if (e.button.button == SDL_BUTTON_RIGHT) {
                            SDL_SetCursor(defaultCursor);
                            // lấy vị trí của con chuột vào x_mouse, y_mouse
                            // nếu click trong hình vuông thì thực hiện xóa cái cũ random cái mới
                            if (isMouseInSquare(x_mouse, y_mouse, x_pos, y_pos, square_size)) {
                                x_pos = rand() % (SCREEN_W - square_size);
                                y_pos = rand () % (SCREEN_H - square_size);
                            }
                        } if (e.button.button == SDL_BUTTON_LEFT) {
                            // HIỆN THÔNG SỐ CỦA MỤC TIÊU (COMMING SOON)
                        }
                    }
                    if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_ESCAPE) {
                            run = true;
                            gameStart = false;
                        }
                        if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_TAB) {
                            SDL_ShowCursor(SDL_ENABLE);
                            SDL_SetCursor(attackCursor);
                        }
                    } 
                    
                }
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                SDL_RenderClear(gRenderer);
                renderSquare(x_pos, y_pos, square_size);
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