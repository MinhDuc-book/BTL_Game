#ifndef INIT_COMMAND_H
#define INIT_COMMAND_H

#include "includeFile.h"

int initialization() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to initialize" << endl;
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "Failed to initialize" << endl;
        SDL_Quit();
        return -1;
    }

    return 0; // Thành công
}

#endif
