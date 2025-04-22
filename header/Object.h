#ifndef OBJECT_H
#define OBJECT_H
#include "includeFile.h"
#include "ReactFunc.h"
using namespace std;

class BaseObject
{
    public:
        int Health;
        float Level = 1;
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
        bool doneAttack;
        int size;
        float range = 200.0f;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        Uint32 frameDelay = 60; // ms

};



class Orc : public BaseObject
{
    public:
        float v = 0;
        int size;
        float range = 10.0;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        const Uint32 frameDelay = 75; // ms

};

class Arrow{
    public:
        float x,y;
        float speed;
        float angle;
        float targetX, targetY;

        Arrow(float startX, float startY, float targetX, float targetY, float s): x(startX), y(startY), speed(s) {
            float dx = targetX - startX;
            float dy = targetY - startY;
            angle = atan2(dy, dx) * 180.0f / PI;
        }

        float calculateAngle(float soldierX, float soldierY, float orcX, float orcY) {
            float dx = orcX - soldierX;
            float dy = orcY - soldierY;
            return atan2(dy, dx) * 180.0f / M_PI; 
        }

        void moveArrow() {
            x = x + cos(angle * PI / 180.0f) * speed;
            y = y + sin(angle * PI / 180.0f) * speed;
        } 

        void renderArrow(SDL_Renderer *renderer) {
            SDL_Rect srcRect = {0, 0, 18, 7};
            SDL_Rect desRect = {static_cast<int> (x), static_cast<int> (y), 100,100};

            arrowTexture = SDL_CreateTextureFromSurface(renderer, arrow);
            SDL_RenderCopyEx(renderer, arrowTexture, &srcRect, &desRect, calculateAngle(x, y, targetX, targetY), NULL, SDL_FLIP_NONE);
        }
};



#endif