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
int const SCREEN_W = 1000;
int const SCREEN_H = 1000;
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

enum soldierState {
    IDLE,
    ATTACK,
    RUN,
    DEATH,
    HURT,
    TOTAL_STATE_CHAR
};


GameState currentState = START;
int selectOption = 0;
int square_size = 20;
int x_mouse = 0;
int y_mouse = 0;
bool run = true;
bool gameStart = false;
int option = 0;
int mouseOption = DEFAULT;
int const PI = 3.14159;
int x_end, y_end;

const char *path_soldier_idle = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Idle.png";
const char *path_soldier_run = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Walk.png";
const char *path_soldier_attack = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Attack03.png";
const char *path_soldier_death = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Death.png";
const char *path_soldier_hurt = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Hurt.png";
const char *path_orc_idle = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Idle.png";
const char *path_orc_run = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Walk.png";
const char *path_orc_attack = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Attack02.png";
const char *path_orc_death = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Death.png";
const char *path_orc_hurt= "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Hurt.png";

const char *path_background = "Background/Grass_24-512x512.png";

SDL_Surface *spriteAttack = IMG_Load(path_soldier_attack);
SDL_Surface *spriteRun = IMG_Load(path_soldier_run);
SDL_Surface *spriteHurt = IMG_Load(path_soldier_hurt);
SDL_Surface *spriteDeath = IMG_Load(path_soldier_death);
SDL_Surface *spriteIdle = IMG_Load (path_soldier_idle);

SDL_Surface *spriteOrcAttack = IMG_Load(path_orc_attack);
SDL_Surface *spriteOrcRun = IMG_Load(path_orc_run);
SDL_Surface *spriteOrcHurt = IMG_Load(path_orc_hurt);
SDL_Surface *spriteOrcDeath = IMG_Load(path_orc_death);
SDL_Surface *spriteOrcIdle = IMG_Load (path_orc_idle);

SDL_Cursor *attackCursor;
SDL_Cursor *defaultCursor;
SDL_Cursor *altCursor;
SDL_Cursor *handWritingCursor;
SDL_Cursor *saveDefaultCursor;

SDL_Texture *gTexture;

SDL_Texture *currentTexture;
SDL_Texture *runTexture;
SDL_Texture *hurtTexture;
SDL_Texture *deathTexture;
SDL_Texture *attackTexture;
SDL_Texture *idleTexture;


SDL_Texture *currentOrcTexture;
SDL_Texture *runOrcTexture;
SDL_Texture *hurtOrcTexture;
SDL_Texture *deathOrcTexture;
SDL_Texture *attackOrcTexture;
SDL_Texture *idleOrcTexture;

#endif