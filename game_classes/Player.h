#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>

#include <vector>

#include "Object.h"
#include "../game_functions/check collisions.h"

class Player{
	private:
		float x, y, z;
		float healthPoints, damagePoints, movementSpeed;
		bool isAlive;
		bool isInvulnerable;
		Object *playerObject;
	public:
		// Constructors
		Player(){
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->healthPoints = 100;
			this->damagePoints = 10;
			this->movementSpeed = 10;
			this->isAlive = true;
			this->isInvulnerable = false;
			this->playerObject = new Object(PLAYER, CUBE, 0, 0, 0, 25, 0, 1, 1);
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

		float getMovementSpeed() {
			return this->movementSpeed;
		}

		bool getIsAlive() {
			return this->isAlive;
		}

		bool getInvulnerability() {
			return this->isInvulnerable;
		}

		Object *getPlayerObject() {
			return this->playerObject;
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

		void setMovementSpeed(float movementSpeed) {
			this->movementSpeed = movementSpeed;
		}

		void setIsAlive(bool isAlive) {
			this->isAlive = isAlive;
		}

		void setInvulnerability(bool isInvulnerable) {
			this->isInvulnerable = isInvulnerable;
		}

		void setPlayerObject(Object *playerObject) {
			this->playerObject = playerObject;
		}

		// Methods
		void resetPlayer() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->healthPoints = 100;
			this->damagePoints = 100;
			this->movementSpeed = 10;
			this->isAlive = true;
			this->isInvulnerable = false;
			this->playerObject = new Object();
		}

		void moveUp() {
			this->y += this->movementSpeed;
			this->playerObject->setCoordinateY(this->y);
		}

		void moveDown() {
			this->y -= this->movementSpeed;
			this->playerObject->setCoordinateY(this->y);
		}

		void moveLeft() {
			this->x -= this->movementSpeed;
			this->playerObject->setCoordinateX(this->x);
		}

		void moveRight() {
			this->x += this->movementSpeed;
			this->playerObject->setCoordinateX(this->x);
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

		void render() {
			if (this->isAlive) {
				this->playerObject->render();
			}
		}
};
#endif
