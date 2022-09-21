#include "vector"

#define TRIANGLE_FACE 0
#define QUAD_FACE 1
#define PENTAGON_FACE 2

class Face {
    private:
        std::vector<int> verticesIndices;
        float normal[3];
        int faceType;
    public:
        // Constructors
        Face(){
            this->verticesIndices = std::vector<int>();
            this->normal[0] = 0;
            this->normal[1] = 0;
            this->normal[2] = 0;
        }

        Face(int v1, int v2, int v3){
            faceType = TRIANGLE_FACE;
            this->verticesIndices = std::vector<int>();
            this->verticesIndices.push_back(v1);
            this->verticesIndices.push_back(v2);
            this->verticesIndices.push_back(v3);
            this->normal[0] = 0;
            this->normal[1] = 0;
            this->normal[2] = 0;
        }

        Face(int v1, int v2, int v3, int v4){
            faceType = QUAD_FACE;
            this->verticesIndices = std::vector<int>();
            this->verticesIndices.push_back(v1);
            this->verticesIndices.push_back(v2);
            this->verticesIndices.push_back(v3);
            this->verticesIndices.push_back(v4);
            this->normal[0] = 0;
            this->normal[1] = 0;
            this->normal[2] = 0;
        }

        Face(int v1, int v2, int v3, int v4, int v5){
            faceType = PENTAGON_FACE;
            this->verticesIndices = std::vector<int>();
            this->verticesIndices.push_back(v1);
            this->verticesIndices.push_back(v2);
            this->verticesIndices.push_back(v3);
            this->verticesIndices.push_back(v4);
            this->verticesIndices.push_back(v5);
            this->normal[0] = 0;
            this->normal[1] = 0;
            this->normal[2] = 0;
        }

        // Getters
        std::vector<int> getVerticesIndices(){
            return this->verticesIndices;
        }

        float* getNormal(){
            return this->normal;
        }

        int getFaceType(){
            return this->faceType;
        }

        // Setters
        void setVerticesIndices(std::vector<int> verticesIndices){
            faceType = verticesIndices.size() - 3;
            this->verticesIndices = verticesIndices;
        }

        void setNormal(float normal[3]){
            this->normal[0] = normal[0];
            this->normal[1] = normal[1];
            this->normal[2] = normal[2];
        }
};
