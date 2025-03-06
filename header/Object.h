#ifndef OBJECT_H
#define OBJECT_H
#include "includeFile.h"

class BaseObject
{
    public:
        int Health;
        int Level;
        int X, Y;
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
        float range = 100.0;
};

#endif