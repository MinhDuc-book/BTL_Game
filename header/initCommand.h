#ifndef INIT_COMMAND_H
#define INIT_COMMAND_H

#include "includeFile.h"
using namespace std;

bool init() {
    bool success = true;
    
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        success = false;
    } else if (TTF_Init() < 0) {
        cout << "Cannot initialize TTF! TTF_Error: " << TTF_GetError() << endl;
        success = false;
    } else {
        // Khởi tạo SDL Image
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            cout << "Failed to initialize SDL Image! IMG_Error: " << IMG_GetError() << endl;
            success = false;
        } else {
            gWindow = SDL_CreateWindow("AimGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
            if (gWindow == nullptr) {
                cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
                success = false;
            } else {
                // Tạo renderer cho cửa sổ
                gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                if (gRenderer == nullptr) {
                    cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
                    success = false;
                } else {
                    // Khởi tạo con trỏ chuột mới
                    SDL_Surface* attackPointer = IMG_Load("Icon/Ping_Target.png");
                    SDL_Surface* defaultPointer = IMG_Load("Icon/defaultCursor.png");
                    if (attackPointer == nullptr || defaultPointer == nullptr) {
                        cout << "Failed to load image! IMG_Error: " << IMG_GetError() << endl;
                        success = false;
                    } else {
                        attackCursor = SDL_CreateColorCursor(attackPointer, attackPointer->w / 2, attackPointer->h / 2);
                        defaultCursor = SDL_CreateColorCursor(defaultPointer, 0, 0);
                        if (attackCursor == nullptr || defaultCursor == nullptr) {
                            cout << "Failed to create cursor! SDL_Error: " << SDL_GetError() << endl;
                            success = false;
                        }
                        SDL_FreeSurface(attackPointer);
                        SDL_FreeSurface(defaultPointer);
                    }
                }
            }
        }
    }
    
    return success;
}

#endif
