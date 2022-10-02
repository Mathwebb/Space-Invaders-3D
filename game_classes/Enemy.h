#ifndef ENEMY_H
#define ENEMY_H

#include <GL/glut.h>

#include "Object.h"

class Enemy{
    private:
        int type;
        float healthPoints, damagePoints, movementSpeed, shotCooldownMiliseconds;
        float movementDirection[3];
        bool isAlive, alreadyShot;
        Object *enemyObject;
    public:
        // Constructors
        Enemy(){
            this->healthPoints = 10;
            this->damagePoints = 10;
            this->movementSpeed = 2;
            this->isAlive = true;
            this->alreadyShot = false;
            this->enemyObject = new Object();
        }

        Enemy(float x, float y, float z){
            this->healthPoints = 10;
            this->damagePoints = 10;
            this->movementSpeed = 2;
            this->movementDirection[0] = rand() % 3 - 1;
            this->movementDirection[1] = 0;
            this->movementDirection[2] = 1;
            this->isAlive = true;
            this->alreadyShot = false;
            this->enemyObject = new Object(ENEMY, SPHERE, x, y, z, 25, 1, 0, 0);
        }

        // Getters
        float getCoordinateX() {
            return this->enemyObject->getCoordinateX();
        }

        float getCoordinateY() {
            return this->enemyObject->getCoordinateY();
        }

        float getCoordinateZ() {
            return this->enemyObject->getCoordinateZ();
        }

        float getHealthPoints() {
            return this->healthPoints;
        }

        float getDamagePoints() {
            return this->damagePoints;
        }

        float getMovementSpeed() {
            return this->movementSpeed;
        }

        float getMovementDirectionX() {
            return this->movementDirection[0];
        }

        float getMovementDirectionY() {
            return this->movementDirection[1];
        }

        float getMovementDirectionZ() {
            return this->movementDirection[2];
        }

        bool getIsAlive() {
            return this->isAlive;
        }

        bool getAlreadyShot() {
            return this->alreadyShot;
        }

        Object *getEnemyObject() {
            return this->enemyObject;
        }

        // Setters
        void setCoordinateX(float x) {
            this->enemyObject->setCoordinateX(x);
        }

        void setCoordinateY(float y) {
            this->enemyObject->setCoordinateY(y);
        }

        void setCoordinateZ(float z) {
            this->enemyObject->setCoordinateZ(z);
        }

        void setHealthPoints(float healthPoints) {
            this->healthPoints = healthPoints;
        }

        void setDamagePoints(float damagePoints) {
            this->damagePoints = damagePoints;
        }

        void setMovementSpeed(float movementSpeed) {
            this->movementSpeed = movementSpeed;
        }

        void setMovementDirectionX(float x) {
            this->movementDirection[0] = x;
        }

        void setMovementDirectionY(float y) {
            this->movementDirection[1] = y;
        }

        void setMovementDirectionZ(float z) {
            this->movementDirection[2] = z;
        }
    
        void setAlreadyShot(bool alreadyShot) {
            this->alreadyShot = alreadyShot;
        }

        void setEnemyObject(Object *enemyObject) {
            this->enemyObject = enemyObject;
        }

        // Methods
        void moveEnemy(){
            this->enemyObject->moveX(this->movementDirection[0] * this->movementSpeed);
            this->enemyObject->moveY(this->movementDirection[1] * this->movementSpeed);
            this->enemyObject->moveZ(this->movementDirection[2] * this->movementSpeed);
        }

        void takeDamage(float damagePoints) {
            if (this->healthPoints - damagePoints <= 0) {
                this->healthPoints = 0;
                this->isAlive = false;
            } else {
                this->healthPoints -= damagePoints;
                cout << healthPoints << endl;
            }
        }

        void Shoot() {
            this->alreadyShot = true;
        }

        void renderObject() {
            if (this->isAlive) {
                this->enemyObject->render();
            }
        }
};
#endif
