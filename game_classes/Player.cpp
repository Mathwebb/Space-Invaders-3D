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

		float getVelocity() {
			return this->velocity;
		}

		bool getInvulnerability() {
			return this->isInvulnerable;
		}

		Object *getPlayerObject() {
			return this->playerObject;
		}

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

		void setVelocity(float velocity) {
			this->velocity = velocity;
		}

		void setInvulnerability(bool isInvulnerable) {
			this->isInvulnerable = isInvulnerable;
		}

		void setPlayerObject(Object *playerObject) {
			this->playerObject = playerObject;
		}
};


