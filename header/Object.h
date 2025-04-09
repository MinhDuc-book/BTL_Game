#ifndef OBJECT_H
#define OBJECT_H
#include "includeFile.h"
using namespace std;

class BaseObject
{
    public:
        int Health;
        int Level;
        int X, Y;
        bool isRunning;
        bool isAttacking;
        bool isDeath;
        bool isHurt;
        bool isIdle;
        int direction;
        
};

class Soldier : public BaseObject
{
    public:
        float v = 5;
        int size;
        float range = 200.0f;
        soldierState state;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        const Uint32 frameDelay = 75; // ms


};

class Orc : public BaseObject
{
    public:
        float v = 2;
        int size;
        float range = 1.0;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        const Uint32 frameDelay = 75; // ms
};

#endif