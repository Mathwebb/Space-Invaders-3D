#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>

#include <math.h>

using namespace std;

enum ObjectType{
    PLAYER,
    ENEMY,
    PROJECTILE,
    POWERUP
};

enum ObjectShape{
    CUBE,
    SPHERE,
    CONE,
    TORUS
};

class Object{
    private:
        int type;
        int shape;
        float x, y, z;
        float colorR, colorG, colorB;
        float collisionRadius;
    public:
        Object(){
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->colorR = 1;
            this->colorG = 1;
            this->colorB = 1;
            this->collisionRadius = 0;
        }

        Object(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
            this->colorR = 1;
            this->colorG = 1;
            this->colorB = 1;
            this->collisionRadius = 0;
        }

        Object(ObjectType type, ObjectShape shape, float x, float y, float z, float collisionRadius){
            this->type = type;
            this->shape = shape;
            this->x = x;
            this->y = y;
            this->z = z;
            this->colorR = 1;
            this->colorG = 1;
            this->colorB = 1;
            this->collisionRadius = collisionRadius;
        }

        Object(ObjectType type, ObjectShape shape, float x, float y, float z, float collisionRadius, float colorR, float colorG, float colorB){
            this->type = type;
            this->shape = shape;
            this->x = x;
            this->y = y;
            this->z = z;
            this->colorR = colorR;
            this->colorG = colorG;
            this->colorB = colorB;
            this->collisionRadius = collisionRadius;
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

        float getCollorR() {
            return this->colorR;
        }

        float getCollorG() {
            return this->colorG;
        }

        float getCollorB() {
            return this->colorB;
        }

        float getCollisionRadius() {
            return this->collisionRadius;
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

        void setColorR(float colorR) {
            this->colorR = colorR;
        }

        void setColorG(float colorG) {
            this->colorG = colorG;
        }

        void setColorB(float colorB) {
            this->colorB = colorB;
        }

        void setCollisionRadius(float collisionRadius) {
            this->collisionRadius = collisionRadius;
        }

        // Methods
        void move(float x, float y, float z) {
            this->x += x;
            this->y += y;
            this->z += z;
        }

        void moveX(float x) {
            this->x += x;
        }

        void moveY(float y) {
            this->y += y;
        }

        void moveZ(float z) {
            this->z += z;
        }

		void render(){
			glPushMatrix();
				glTranslatef(this->x, this->y, this->z);
				glColor3f(this->colorR, this->colorG, this->colorB);
				if (this->shape == CUBE){
					glutSolidCube(this->collisionRadius);
				}else if (this->shape == SPHERE){
					glutSolidSphere(this->collisionRadius, 20, 20);
				}else if (this->shape == CONE){
					glutSolidCone(this->collisionRadius/2, this->collisionRadius, 20, 20);
				}else if (this->shape == TORUS){
					glutSolidTorus(this->collisionRadius/2, this->collisionRadius, 20, 20);
				}
			glPopMatrix();	
		}

        bool checkCollision(Object *object) {
            float distance = sqrt(pow(this->x - object->getCoordinateX(), 2) + pow(this->y - object->getCoordinateY(), 2) + pow(this->z - object->getCoordinateZ(), 2));
            if (distance <= this->collisionRadius + object->getCollisionRadius()) {
                return true;
            }
            return false;
        }

        bool checkCollision(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
            if (this->x + this->collisionRadius >= xMin && this->x - this->collisionRadius <= xMax
                && this->y + this->collisionRadius >= yMin && this->y - this->collisionRadius <= yMax
                && this->z + this->collisionRadius >= zMin && this->z - this->collisionRadius <= zMax) {
                return true;
            }
            return false;
        }
};
#endif
