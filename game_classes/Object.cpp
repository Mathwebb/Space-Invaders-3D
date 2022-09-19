#include <vector>
#include "Face.cpp"

class Object{
	public:
		std::vector<Vertex> vertices;
		std::vector<Face> faces;
		float posX, posY, posZ;
		float angle, angleX, angleY, angleZ;
		float scaleX, scaleY, scaleZ;
		Object(std::vector<Vertex> vertices, std::vector<Face> faces) {
			this->vertices = vertices;
			this->faces = faces;
			this->posX = 0;
			this->posY = 0;
			this->posZ = 0;
			this->angle = 0;
			this->angleX = 0;
			this->angleY = 0;
			this->angleZ = 0;
			this->scaleX = 0;
			this->scaleY = 0;
			this->scaleZ = 0;
		}
};
