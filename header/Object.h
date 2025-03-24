#ifndef OBJECT_H
#define OBJECT_H
#include "includeFile.h"

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
        soldierState state;
};

class Soldier : public BaseObject
{
    public:
        int velocity_x, velocity_y;
        int size;
        float range = 100.0;
};

class Orc : public BaseObject
{
    public:
        int velocity_x, velocity_y;
        int size;
        float range = 120.0;
};

#endif