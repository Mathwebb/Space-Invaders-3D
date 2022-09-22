#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../game_classes/Object.h"

class Projectile{
    private:
        float x, y, z;
        float damagePoints, movementSpeed;
        bool isAlive;
        Object *projectileObject;
    public:
        // Constructors
        Projectile(){
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->damagePoints = 10;
            this->movementSpeed = 10;
            this->isAlive = true;
            this->projectileObject = new Object();
        }

        Projectile(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
            this->damagePoints = 10;
            this->movementSpeed = 10;
            this->isAlive = true;
            this->projectileObject = new Object();
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
            this->x += x;
        }

        
};

#endif
