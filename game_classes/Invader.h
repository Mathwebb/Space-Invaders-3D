#ifndef INVADER_H
#define INVADER_H

#include <GL/glut.h>

#include "Object.h"

// Enemy types
#define weakling 0
#define soldier 1
#define commander 2

class Enemy{
    private:
        int type;
        float x, y, z;
        float healthPoints, damagePoints, movementSpeed;
        bool isAlive;
        Object *enemyObject;
    public:
        // Constructors
        Enemy(){
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->healthPoints = 100;
            this->damagePoints = 10;
            this->movementSpeed = 10;
            this->isAlive = true;
            this->enemyObject = new Object();
        }

        Enemy(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
            this->healthPoints = 100;
            this->damagePoints = 10;
            this->movementSpeed = 10;
            this->isAlive = true;
            this->enemyObject = new Object(ENEMY, SPHERE, this->x, this->y, this->z, 25, 1, 0, 0);
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
            this->x = x;
        }

        void setCoordinateY(float y) {
            this->y = y;
        }

        void setCoordinateZ(float z) {
            this->z = z;
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
        void move(float x, float y, float z) {
            this->x += x;
            this->y += y;
            this->z += z;
        }

        void takeDamage(float damagePoints) {
            this->healthPoints -= damagePoints;
        }

        void render() {
            if (this->isAlive) {
                glPushMatrix();
                glTranslatef(this->x, this->y, this->z);
                glColor3f(1.0, 0.0, 0.0);
                glutWireSphere(25, 20, 20);
                glPopMatrix();
            }
        }
};
#endif
