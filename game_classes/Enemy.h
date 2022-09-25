#ifndef ENEMY_H
#define ENEMY_H

#include <GL/glut.h>

#include "Object.h"

// Enemy types
#define weakling 0
#define soldier 1
#define commander 2

class Enemy{
    private:
        int type;
        float healthPoints, damagePoints, movementSpeed;
        float movementDirection[3];
        bool isAlive;
        Object *enemyObject;
    public:
        // Constructors
        Enemy(){
            this->healthPoints = 100;
            this->damagePoints = 10;
            this->movementSpeed = 10;
            this->isAlive = true;
            this->enemyObject = new Object();
        }

        Enemy(float x, float y, float z){
            this->healthPoints = 100;
            this->damagePoints = 10;
            this->movementSpeed = 10;
            this->movementDirection[0] = rand() % 2;
            this->movementDirection[1] = rand() % 2;
            this->movementDirection[2] = rand() % 2;
            this->isAlive = true;
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
            }
        }

        void renderObject() {
            if (this->isAlive) {
                this->enemyObject->render();
            }
        }
};
#endif
