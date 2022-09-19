#include <vector>
#include "Object.cpp"

class Player{
	private:
		float x, y, z;
		float healthPoints, damagePoints, velocity;
		bool isInvulnerable;
		Object *playerObject;
		// std::vector<string> powerups;
	public:
		float getCoordinateX();
		float getCoordinateY();
		float getCoordinateZ();
		float getHealthPoints();
		float getDamagePoints();
		float getVelocity();
		bool getInvulnerability();
		Object *getPlayerObject();
		// std::vector<string> getPowerups();
		void setCoordinateX(float x);
		void setCoordinateY(float y);
		void setCoordinateZ(float z);
		void setHealthPoints(float healthPoints);
		void setDamagePoints(float damagePoints);
		void setVelocity(float velocity);
		void setInvulnerability(bool isInvulnerable);
		void setPlayerObject(Object *playerObject);
};

float Player::getCoordinateX() {
	return this->x;
}

float Player::getCoordinateY() {
	return this->y;
}

float Player::getCoordinateZ() {
	return this->z;
}

float Player::getHealthPoints() {
	return this->healthPoints;
}

float Player::getDamagePoints() {
	return this->damagePoints;
}

float Player::getVelocity() {
	return this->velocity;
}

bool Player::getInvulnerability() {
	return this->isInvulnerable;
}

Object *Player::getPlayerObject() {
	return this->playerObject;
}

void Player::setCoordinateX(float x) {
	this->x = x;
}

void Player::setCoordinateY(float y) {
	this->y = y;
}

void Player::setCoordinateZ(float z) {
	this->z = z;
}

void Player::setHealthPoints(float healthPoints) {
	this->healthPoints = healthPoints;
}

void Player::setDamagePoints(float damagePoints) {
	this->damagePoints = damagePoints;
}

void Player::setVelocity(float velocity) {
	this->velocity = velocity;
}

void Player::setInvulnerability(bool isInvulnerable) {
	this->isInvulnerable = isInvulnerable;
}

void Player::setPlayerObject(Object *playerObject) {
	this->playerObject = playerObject;
}
