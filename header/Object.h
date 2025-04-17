#ifndef OBJECT_H
#define OBJECT_H
#include "includeFile.h"
using namespace std;

class BaseObject
{
    public:
        int Health;
        float Level;
        int X, Y;
        bool isRunning;
        bool isAttacking;
        bool isDeath;
        bool isHurt;
        bool isIdle;
        float angle;
        SDL_RendererFlip flip = SDL_FLIP_NONE;

};

class Soldier : public BaseObject
{
    public:
        float v = 4;
        bool doneDeath = false;
        int size;
        float range = 200.0f;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        Uint32 frameDelay = 85; // ms

};

class Orc : public BaseObject
{
    public:
        float v = 1;
        int size;
        float range = 10.0;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        const Uint32 frameDelay = 75; // ms

};



#endif