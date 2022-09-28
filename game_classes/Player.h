#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>

#include <vector>

#include "Object.h"

class Player{
	private:
		float healthPoints, damagePoints, movementSpeed;
		float shotCooldownMiliseconds, invulnerabilityTimeMiliseconds;
		bool isAlive, isInvulnerable, isShooting;
		Object *playerObject;
	public:
		// Constructors
		Player(){
			this->healthPoints = 100;
			this->damagePoints = 10;
			this->movementSpeed = 10;
			this->shotCooldownMiliseconds = 1000;
			this->invulnerabilityTimeMiliseconds = 0;
			this->isAlive = true;
			this->isInvulnerable = false;
			this->isShooting = false;
			this->playerObject = new Object(PLAYER, CONE, 30, 30, 0, 25, 0, 1, 1);
		}

		// Getters
		float getCoordinateX() {
			return this->playerObject->getCoordinateX();
		}

		float getCoordinateY() {
			return this->playerObject->getCoordinateY();
		}

		float getCoordinateZ() {
			return this->playerObject->getCoordinateZ();
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

		float getShotCooldownMiliseconds() {
			return this->shotCooldownMiliseconds;
		}

		float getInvulnerabilityTimeMiliseconds() {
			return this->invulnerabilityTimeMiliseconds;
		}

		bool getIsAlive() {
			return this->isAlive;
		}

		bool getInvulnerability() {
			return this->isInvulnerable;
		}

		bool getIsShooting() {
			return this->isShooting;
		}

		Object *getPlayerObject() {
			return this->playerObject;
		}

		// Setters
		void setCoordinateX(float x) {
			this->playerObject->setCoordinateX(x);
		}

		void setCoordinateY(float y) {
			this->playerObject->setCoordinateY(y);
		}

		void setCoordinateZ(float z) {
			this->playerObject->setCoordinateZ(z);
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

		void setShotCooldownMiliseconds(float shotCooldownMiliseconds) {
			this->shotCooldownMiliseconds = shotCooldownMiliseconds;
		}

		void setInvulnerabilityTimeMiliseconds(float invulnerabilityTimeMiliseconds) {
			this->invulnerabilityTimeMiliseconds = invulnerabilityTimeMiliseconds;
		}

		void setIsAlive(bool isAlive) {
			this->isAlive = isAlive;
		}

		void setInvulnerability(bool isInvulnerable) {
			this->isInvulnerable = isInvulnerable;
		}
		
		void setIsShooting(bool isShooting) {
			this->isShooting = isShooting;
		}

		void setPlayerObject(Object *playerObject) {
			this->playerObject = playerObject;
		}

		// Methods
		void resetPlayer() {
			this->healthPoints = 100;
			this->damagePoints = 100;
			this->movementSpeed = 10;
			this->isAlive = true;
			this->isInvulnerable = false;
			this->playerObject = new Object(PLAYER, CONE, 30, 30, 0, 25, 0, 1, 1);
		}

		void moveUp() {
			this->playerObject->moveY(this->movementSpeed);
		}

		void moveDown() {
			this->playerObject->moveY(-this->movementSpeed);
		}

		void moveLeft() {
			this->playerObject->moveX(-this->movementSpeed);
		}

		void moveRight() {
			this->playerObject->moveX(this->movementSpeed);
		}

		void takeDamage(float damagePoints) {
			if (healthPoints - damagePoints <= 0) {
				this->healthPoints = 0;
				this->isAlive = false;
			}
			else {
				this->healthPoints -= damagePoints;
			}
		}

		void heal(float healthPoints) {
			if (this->healthPoints + healthPoints >= 100) {
				this->healthPoints = 100;
			}
			else {
				this->healthPoints += healthPoints;
			}
		}

		void renderObject() {
			if (this->isAlive) {
				this->playerObject->render();
			}
		}

		void resetShot() {
			this->isShooting = false;
		}
};
#endif
