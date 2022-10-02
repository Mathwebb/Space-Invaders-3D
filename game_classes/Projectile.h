#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../game_classes/Object.h"

enum ProjectileOwner{PLAYER_PROJECTILE, ENEMY_PROJECTILE};

class Projectile{
    private:
        ProjectileOwner owner;
        float damagePoints, movementSpeed;
        bool isAlive;
        Object *projectileObject;
    public:
        // Constructors
        Projectile(ProjectileOwner owner, float x, float y, float z){
            this->owner = owner;
            this->damagePoints = 10;
            this->movementSpeed = 20;
            this->isAlive = true;
            if(owner==PLAYER_PROJECTILE){
				this->projectileObject = new Object(PROJECTILE, SPHERE, x, y, z, 10, 1, 1, 0);
			}
			else{
				this->projectileObject = new Object(PROJECTILE, SPHERE, x, y, z, 10, 0, 1, 0);
			}
            
        }

        // Getters
        ProjectileOwner getOwner() {
            return this->owner;
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

        Object *getProjectileObject() {
            return this->projectileObject;
        }

        // Setters
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
        void moveProjectile() {
            if (this->owner == PLAYER_PROJECTILE) {
                this->projectileObject->moveZ(- this->getMovementSpeed());
            } else if (this->owner == ENEMY_PROJECTILE) {
                this->projectileObject->moveZ(this->getMovementSpeed());
            }
        }

        void renderObject() {
            if (this->isAlive) {
            this->projectileObject->render();
            }
        }
};

#endif
