#include "vector"
#include "Vertex.cpp"

class Face {
    public:
        std::vector<Vertex> vertices;
        float normal[3];
        Face(std::vector<Vertex> vertices) {
            this->vertices = vertices;
        }
};
