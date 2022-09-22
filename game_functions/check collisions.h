#ifndef CHECK_COLLISIONS_H
#define CHECK_COLLISIONS_H

#include "../game_classes/Object.h"

bool checkObjectsCollision(Object *object1, Object *object2){
    return object1->checkCollision(object2);
}

bool checkBordersCollision(Object *object, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax){
    return object->checkCollision(xMin, xMax, yMin, yMax, zMin, zMax);
}

#endif