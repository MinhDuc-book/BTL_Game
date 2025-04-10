#ifndef REACT_FUNCTION_H
#define REACT_FUNCTION_H

#include "includeFile.h"
#include "Object.h"
#include "commonVar.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>

bool isMouseInSquare(int x, int y, Orc orc) {
    if (x <= orc.size + orc.X and x >= orc.X - orc.size and y <= orc.Y + orc.size and y >= orc.Y - orc.size) {
        return true;
    }
    return false;
}

bool isInRange(Soldier soldier, Orc orc) {
    float dx = soldier.X - orc.X;
    float dy = soldier.Y - orc.Y;
    float distance = sqrt(dx*dx + dy*dy) - orc.size;
    return distance <= soldier.range;
}

int createRandom(int a, int b) {
    srand(time(0));
    int randomNumber = a + rand() % (b - a + 1);

    return randomNumber;
}

float getDistance(int x1, int y1, int x2, int y2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    float distance = sqrt (dx * dx + dy * dy);

    return distance;

}
void createMoreOrc(LinkedList &orc, int numberOfOrc) {
    Object *temp = new Object {createRandom(0, SCREEN_W), createRandom(0, SCREEN_H)};
    orc.insertAtEnd(temp);
    numberOfOrc++;
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

#endif