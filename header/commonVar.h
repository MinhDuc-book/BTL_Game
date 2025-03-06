#ifndef COMMON_VAR_H
#define COMMON_VAR_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <SDL2/SDL_ttf.h>

// các biến toàn chương trình dùng cho SDL
int const SCREEN_W = 1280;
int const SCREEN_H = 720;
int const SCREEN_BPP = 32;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

enum KeyPress {
    KEY_PRESS_DEFAULT,
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_ENTER,
    KEY_PRESS_ESCAPE,
    KEY_PRESS_TOTAL
};

enum GameState {
    START,
    HIGH_SCORE,
    QUIT,
    STATE_TOTAL
};

GameState currentState = START;
int selectOption = 0;
int x_pos = 0;
int y_pos = 0;
int square_size = 20;
int x_mouse = 0;
int y_mouse = 0;
bool run = true;
bool gameStart = false;
int option = 0;
int const PI = 3.14159;
float v = 0; // biến vận tốc nhân vật
int x_end, y_end;

SDL_Cursor *attackCursor;
SDL_Cursor *defaultCursor;
#endif