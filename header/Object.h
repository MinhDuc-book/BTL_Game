#ifndef OBJECT_H
#define OBJECT_H

#include "includeFile.h"
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
        bool ironBody = false;
        int size;
        float range = 200.0f;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        Uint32 frameDelay = 60; 

};



class Orc : public BaseObject
{
    public:
        float v = 1;
        bool doneDeath = false;
        int size;
        float range = 10.0;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        Uint32 frameDelay = 75; // ms

};

class Arrow 
{
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

        void moveArrow() {
            if (x != targetX and y != targetY and x <= SCREEN_W and y <= SCREEN_H) {
                Mix_PlayChannel(-1, arrowMoveSound, 0);
            }

            x = x + cos(angle * PI / 180.0f) * speed;
            y = y + sin(angle * PI / 180.0f) * speed;

            float dx = targetX - x;
            float dy = targetY - y;
            float distance = sqrt(dx * dx + dy * dy);
            if (distance < 5.0f) {
                x = targetX;
                y = targetY;
            }
        }

        bool checkColid(int orcX, int orcY, int orcsize) {
            float dx = x - orcX;
            float dy = y - orcY;
            float distance = sqrt(dx * dx + dy * dy);

            return distance < orcsize / 2;
        }

        void renderArrow(SDL_Renderer *renderer) {
             
            SDL_Rect srcRect = {0, 0, 18, 7};
            SDL_Rect desRect = {static_cast<int> (x), static_cast<int> (y), 30, 30};
            arrowTexture = SDL_CreateTextureFromSurface(renderer, arrowSurface);

            SDL_RenderCopyEx(renderer, arrowTexture, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
        }
};




#endif