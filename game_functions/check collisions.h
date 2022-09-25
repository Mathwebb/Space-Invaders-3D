#ifndef CHECK_COLLISIONS_H
#define CHECK_COLLISIONS_H

#include "../game_classes/Object.h"
#include "../game_classes/Level.h"

bool checkObjectsCollision(Object *object1, Object *object2){
    return object1->checkCollision(object2);
}

#endif