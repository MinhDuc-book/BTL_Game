#ifndef REACT_FUNCTION_H
#define REACT_FUNCTION_H

#include "includeFile.h"
#include "Object.h"
#include "commonVar.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath>
#include <fstream>

bool isMouseInSquare(int x, int y, Orc orc) {
    if (x <= orc.size + (orc.X) and x >= orc.X - orc.size and y <= orc.Y + orc.size and y >= orc.Y - orc.size) {
        return true;
    }
    return false;
}

int getDistance(Soldier &soldier, Orc &orc) {
    float dx = soldier.X - orc.X;
    float dy = soldier.Y - orc.Y;

    int distance = sqrt(dx*dx + dy*dy);
    return distance;
}

bool isInRange(Soldier soldier, Orc orc) {
    float dx = soldier.X - orc.X;
    float dy = soldier.Y - orc.Y;
    float distance = sqrt(dx*dx + dy*dy) - orc.size;
    return distance <= soldier.range;
}

double getAngle(Soldier soldier, Orc orc) {
    double dx = soldier.X - orc.X;
    double dy = soldier.Y - orc.Y;
    double angle = atan2(dy, dx) * 180 / PI;

    if (angle < 0) {
        angle = angle + 360;
    }

    return angle;
}

bool isInRangeOrc(Soldier soldier, Orc orc) {
    float dx = soldier.X - orc.X;
    float dy = soldier.Y - orc.Y;
    float distance = sqrt(dx*dx + dy*dy) - soldier.size;
    return distance <= orc.range;
}

int createRandom(int a, int b) {
    srand(time(0));
    int randomNumber = a + rand() % (b - a + 1);

    return randomNumber;
}

void movePlayer(Soldier &soldier, int x_mouse, int y_mouse, float v) {
    float dx = x_mouse - soldier.X;
    float dy = y_mouse - soldier.Y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > v) {
        float stepX = v * (dx / distance);
        float stepY = v * (dy / distance);

        soldier.X += stepX;
        soldier.Y += stepY;
    } else if (distance > 0) {
        soldier.X = x_mouse;
        soldier.Y = y_mouse;
    }
    
}


void restartGame(Soldier &soldier, Orc &orc, int &Score) {
    soldier.X = SCREEN_W / 2;
    soldier.Y = SCREEN_H / 2;
    soldier.isIdle = true;
    soldier.isDeath = false;
    soldier.isRunning = false;
    soldier.Health = 2500;

    orc.X = 100;
    orc.Y = 100;

    isSavedScore = false;

    Score = 0;  
}

void moveOrc(Orc &orc, Soldier soldier, float v) {
    float dx = soldier.X - orc.X;
    float dy = soldier.Y - orc.Y;
    float distance = sqrt (dx * dx + dy * dy);

    if (distance > v) {
        float stepX = v * (dx/distance > 0 ? 1 : -1);
        float stepY = v * (dy/distance > 0 ? 1 : -1);

        orc.X += stepX;
        orc.Y += stepY;
        
    } else if (distance > 0) {
        orc.X = soldier.X;
        orc.Y = soldier.Y;
    }

}

void saveScore(int Score, const char *path_score) {
    ofstream file(path_score, ios::app);
    if (file.is_open() == false) {
        cout <<"Cannot open file" << endl;
    } else {
        if (isSavedScore == false) {
            file << Score << endl;
            file.close();
            isSavedScore = true;
        } 
    }
}

int findHighestScore(const char *path_score) {
    int highestScore = 0;
    ifstream inFile(path_score);
    if (inFile.is_open() == false) {
        cout << "Cannot open file" << endl;
    }  else {
        int numberInFile;
        while (inFile >> numberInFile) {
            if (numberInFile > highestScore) {
                highestScore = numberInFile;
            }
        }
    }
    return highestScore;
}

int findLowestScore(const char *path_score) {
    int lowestScore = 100000;
    ifstream inFile(path_score);
    if (inFile.is_open() == false) {
        cout << "Cannot open file" << endl;
    }  else {
        int numberInFile;
        while (inFile >> numberInFile) {
            if (numberInFile < lowestScore) {
                lowestScore = numberInFile;
            }
        }
    }
    return lowestScore;
}

int findAverageScore(const char *path_score) {
    double averageScore = 0;
    int count = 0;
    ifstream inFile(path_score);
    if (inFile.is_open() == false) {
        cout << "Cannot open file" << endl;
    } else {
        int numberInFile;
        while (inFile >> numberInFile) {
            count++;
            averageScore = averageScore + numberInFile;
        }
    }
    return round(averageScore / count);
}

void close() 
{
    SDL_DestroyTexture(hurtTexture);
    SDL_DestroyTexture(idleTexture);
    SDL_DestroyTexture(runOrcTexture);
    SDL_DestroyTexture(runTexture);
    SDL_DestroyTexture(attackTexture);
    SDL_DestroyTexture(splitTexture);

    SDL_DestroyTexture(attackOrcTexture);
    SDL_DestroyTexture(idleOrcTexture);
    SDL_DestroyTexture(hurtOrcTexture);
    SDL_DestroyTexture(deathOrcTexture);
    SDL_DestroyTexture(arrowTexture);

    SDL_FreeCursor(attackCursor);
    SDL_FreeCursor(defaultCursor);
    SDL_FreeCursor(altCursor);
    SDL_FreeCursor(handWritingCursor);
    SDL_FreeCursor(saveDefaultCursor);

    SDL_FreeSurface(spriteOrcAttack);
    SDL_FreeSurface(spriteOrcRun);
    SDL_FreeSurface(spriteOrcHurt);
    SDL_FreeSurface(spriteOrcDeath);
    SDL_FreeSurface(spriteOrcIdle);

    SDL_FreeSurface(spriteAttack);
    SDL_FreeSurface(spriteAttack1);
    SDL_FreeSurface(spriteAttack2);
    SDL_FreeSurface(spriteRun);
    SDL_FreeSurface(spriteHurt);
    SDL_FreeSurface(spriteDeath);
    SDL_FreeSurface(spriteIdle);
    SDL_FreeSurface(splitAttack);
    SDL_FreeSurface(arrowSurface);

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

#endif