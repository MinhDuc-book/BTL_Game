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
    SETTING,
    QUIT,
    STATE_TOTAL
};

enum mouseOption {
    DEFAULT,
    ALT_IMAGE,
    HANDWRITING,
    TOTAL_MOUSE_OPTION
};

GameState currentState = START;
int selectOption = 0;
int x_pos = 50;
int y_pos = 50;
int square_size = 20;
int x_mouse = 0;
int y_mouse = 0;
bool run = true;
bool gameStart = false;
int option = 0;
int mouseOption = DEFAULT;
int const PI = 3.14159;
float v = 0; // biến vận tốc nhân vật
int x_end, y_end;

const char *path_soldier_idle = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Idle.png";
const char *path_orc_idle = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Idle.png";

SDL_Cursor *attackCursor;
SDL_Cursor *defaultCursor;
SDL_Cursor *altCursor;
SDL_Cursor *handWritingCursor;
SDL_Cursor *saveDefaultCursor;

SDL_Texture  *gTexture;

#endif