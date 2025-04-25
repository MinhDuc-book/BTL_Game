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
#include <SDL2/SDL_mixer.h>
#include "includeFile.h"

int const SCREEN_W = 1190;
int const SCREEN_H = 700;


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Surface *scoreSurface = NULL;
SDL_Texture *scoreTexture = NULL;

SDL_Surface *gameOverSurface = NULL;
SDL_Texture *gameOverTexture = NULL;

SDL_Surface *healthBarSurface = IMG_Load("data/healthBarImage - Copy - Copy.png");
SDL_Texture *healthBarTexture = NULL;

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
    RESTART,
    SETTING,
    SCORE,
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
int square_size = 20;
int x_mouse = 0;
int y_mouse = 0;
int option = 0;
int mouseOption = DEFAULT;
int const PI = M_PI;
int x_end = SCREEN_W / 2, y_end = SCREEN_H / 2;
int Score = 0;
bool run = true;
bool gameStart = false;
bool isSavedScore = false;
const char *game_over = "Game Over";
const char *path_score = "data/High-Score.txt";

const char *path_soldier_idle = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Idle.png";
const char *path_soldier_run = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Walk.png";
const char *path_soldier_attack = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Attack03.png";
const char *path_soldier_attack2 = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Attack02.png";
const char *path_soldier_attack1 = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Attack01.png";
const char *path_soldier_death = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Death.png";
const char *path_soldier_hurt = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Hurt.png";
const char *path_split_attack = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier(Split Effects)/Soldier-Attack01_Effect.png";
const char *path_arrow = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Arrow(Projectile)/Arrow01(32x32).png";

const char *path_orc_idle = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Idle.png";
const char *path_orc_run = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Walk.png";
const char *path_orc_attack = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Attack02.png";
const char *path_orc_death = "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Death-Extended.png";
const char *path_orc_hurt= "Characters/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Orc/Orc/Orc-Hurt.png";

const char *path_attackDone_sound = "data/Sound/attackDoneSound.wav";
const char *path_death_sound = "data/Sound/deathSound.wav";
const char *path_hurt_sound = "data/Sound/hurtSound.wav";
const char *path_newHighScore = "data/Sound/newHighScoreSound.wav";
const char *path_arrow_move = "data/Sound/arrowMove.wav";
const char *path_arrow_shoot = "data/Sound/arrowShoot.wav";
const char *path_colid_sound = "data/Sound/colidSound.wav";
const char *path_walk = "data/Sound/walkSound.wav";

int highestScore;

const char *path_background = "Background/Background.png";
SDL_Surface *surfaceBackground;
SDL_Texture *textureBackground;

Mix_Chunk *hurtSound = NULL;
Mix_Chunk *newHighScoreSound = NULL;
Mix_Chunk *arrowMoveSound = NULL;
Mix_Chunk *arrowShootSound = NULL;
Mix_Chunk *colidSound = NULL;
Mix_Chunk *walkSound = NULL;

const char *path_blind_box = "Icon/blindBox.png";
SDL_Surface *blindBoxSurface = IMG_Load(path_blind_box);
SDL_Texture *blindBoxTexture = NULL;

SDL_Surface *spriteAttack = IMG_Load(path_soldier_attack);
SDL_Surface *spriteAttack2 = IMG_Load(path_soldier_attack2);
SDL_Surface *spriteAttack1 = IMG_Load(path_soldier_attack1);
SDL_Surface *spriteRun = IMG_Load(path_soldier_run);
SDL_Surface *spriteHurt = IMG_Load(path_soldier_hurt);
SDL_Surface *spriteDeath = IMG_Load(path_soldier_death);
SDL_Surface *spriteIdle = IMG_Load (path_soldier_idle);
SDL_Surface *splitAttack = IMG_Load(path_split_attack);
SDL_Surface *arrowSurface = IMG_Load(path_arrow);

SDL_Surface *spriteOrcAttack = IMG_Load(path_orc_attack);
SDL_Surface *spriteOrcRun = IMG_Load(path_orc_run);
SDL_Surface *spriteOrcHurt = IMG_Load(path_orc_hurt);
SDL_Surface *spriteOrcDeath = IMG_Load(path_orc_death);
SDL_Surface *spriteOrcIdle = IMG_Load (path_orc_idle);

SDL_Cursor *attackCursor = NULL;
SDL_Cursor *defaultCursor = NULL;
SDL_Cursor *altCursor = NULL;
SDL_Cursor *handWritingCursor = NULL;
SDL_Cursor *saveDefaultCursor = NULL;

SDL_Texture *gTexture = NULL;

SDL_Texture *currentTexture = NULL;
SDL_Texture *runTexture = NULL;
SDL_Texture *hurtTexture = NULL;
SDL_Texture *deathTexture = NULL;
SDL_Texture *attackTexture = NULL;
SDL_Texture *idleTexture = NULL;
SDL_Texture *splitTexture = NULL;
SDL_Texture *arrowTexture = NULL;


SDL_Texture *currentOrcTexture = NULL;
SDL_Texture *runOrcTexture = NULL;
SDL_Texture *hurtOrcTexture = NULL;
SDL_Texture *deathOrcTexture = NULL;
SDL_Texture *attackOrcTexture = NULL;
SDL_Texture *idleOrcTexture = NULL;

#endif