#include <vector>
#include "Face.cpp"
#include "Vertex.cpp"

class Object{
	private:
		std::vector<Vertex> vertices;
		std::vector<Face> faces;
		float x, y, z;
		float rotationAngle;
		bool rotationX, rotationY, rotationZ;
		float scaleX, scaleY, scaleZ;
		float colisionRadius;
	public:
		// Constructors
		Object(){
			this->vertices = std::vector<Vertex>();
			this->faces = std::vector<Face>();
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->rotationAngle = 0;
			this->rotationX = false;
			this->rotationY = false;
			this->rotationZ = false;
			this->scaleX = 1;
			this->scaleY = 1;
			this->scaleZ = 1;
			this->colisionRadius = 0;
		}

		Object(std::vector<Vertex> vertices, std::vector<Face> faces){
			this->vertices = vertices;
			this->faces = faces;
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->rotationAngle = 0;
			this->rotationX = false;
			this->rotationY = false;
			this->rotationZ = false;
			this->scaleX = 1;
			this->scaleY = 1;
			this->scaleZ = 1;
			this->colisionRadius = 0;
		}

		Object(std::vector<Vertex> vertices, std::vector<Face> faces, float x, float y, float z){
			this->vertices = vertices;
			this->faces = faces;
			this->x = x;
			this->y = y;
			this->z = z;
			this->rotationAngle = 0;
			this->rotationX = false;
			this->rotationY = false;
			this->rotationZ = false;
			this->scaleX = 1;
			this->scaleY = 1;
			this->scaleZ = 1;
			this->colisionRadius = 0;
		}

		// Getters
		std::vector<Vertex> getVertices(){
			return this->vertices;
		}

		std::vector<Face> getFaces(){
			return this->faces;
		}

		float getCoordinateX(){
			return this->x;
		}

		float getCoordinateY(){
			return this->y;
		}

		float getCoordinateZ(){
			return this->z;
		}

		float getRotationAngle(){
			return this->rotationAngle;
		}

		bool getRotationX(){
			return this->rotationX;
		}

		bool getRotationY(){
			return this->rotationY;
		}

		bool getRotationZ(){
			return this->rotationZ;
		}

		float getScaleX(){
			return this->scaleX;
		}

		float getScaleY(){
			return this->scaleY;
		}

		float getScaleZ(){
			return this->scaleZ;
		}

		float getColisionRadius(){
			return this->colisionRadius;
		}

		// Setters
		void setVertices(std::vector<Vertex> vertices){
			this->vertices = vertices;
		}

		void setFaces(std::vector<Face> faces){
			this->faces = faces;
		}

		void setCoordinateX(float x){
			this->x = x;
		}

		void setCoordinateY(float y){
			this->y = y;
		}

		void setCoordinateZ(float z){
			this->z = z;
		}

		void setRotationAngle(float angle){
			this->rotationAngle = angle;
		}

		void setRotationX(bool rotationX){
			this->rotationX = rotationX;
		}

		void setRotationY(bool rotationY){
			this->rotationY = rotationY;
		}

		void setRotationZ(bool rotationZ){
			this->rotationZ = rotationZ;
		}

		void setScaleX(float scaleX){
			this->scaleX = scaleX;
		}

		void setScaleY(float scaleY){
			this->scaleY = scaleY;
		}

		void setScaleZ(float scaleZ){
			this->scaleZ = scaleZ;
		}

		void setColisionRadius(float colisionRadius){
			this->colisionRadius = colisionRadius;
		}

		// Methods
		void addVertex(Vertex vertex){
			this->vertices.push_back(vertex);
		}

		void addFace(Face face){
			this->faces.push_back(face);
		}
};
