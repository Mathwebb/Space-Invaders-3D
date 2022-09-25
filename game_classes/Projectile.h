#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../game_classes/Object.h"

class Projectile{
    private:
        ObjectType type;
        float x, y, z;
        float damagePoints, movementSpeed;
        bool isAlive;
        Object *projectileObject;
    public:
        // Constructors
        Projectile(ObjectType type, float x, float y, float z){
            this->type = type;
            this->x = x;
            this->y = y;
            this->z = z;
            this->damagePoints = 10;
            this->movementSpeed = 10;
            this->isAlive = true;
            this->projectileObject = new Object(PROJECTILE, SPHERE, this->x, this->y, this->z, 10, 1, 1, 0);
        }

        // Getters
        float getCoordinateX() {
            return this->x;
        }

        float getCoordinateY() {
            return this->y;
        }

        float getCoordinateZ() {
            return this->z;
        }

        float getDamagePoints() {
            return this->damagePoints;
        }

        float getMovementSpeed() {
            return this->movementSpeed;
        }

        bool getIsAlive() {
            return this->isAlive;
        }

        // Setters
        void setCoordinateX(float x) {
            this->x = x;
        }

        void setCoordinateY(float y) {
            this->y = y;
        }

        void setCoordinateZ(float z) {
            this->z = z;
        }

        void setDamagePoints(float damagePoints) {
            this->damagePoints = damagePoints;
        }

        void setMovementSpeed(float movementSpeed) {
            this->movementSpeed = movementSpeed;
        }

        void setIsAlive(bool isAlive) {
            this->isAlive = isAlive;
        }

        // Methods
        void moveProjectileX(float x) {
            if (this->type == PLAYER) {
                this->x += x;
            } else {
                this->x -= x;
            }
        }

        
};

#endif
