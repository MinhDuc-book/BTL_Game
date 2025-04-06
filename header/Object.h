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
        int direction;
        
};

class Soldier : public BaseObject
{
    public:
        int velocity_x, velocity_y;
        int size;
        float range = 200.0f;
        soldierState state;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        const Uint32 frameDelay = 100; // ms


};

class Orc : public BaseObject
{
    public:
        int velocity_x, velocity_y;
        int size;
        float range = 220.0;
};

#endif