#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "../game_classes/Object.cpp"
using namespace std;

Object loadObject(string filename) {
    fstream file("assets/porsche_clear.obj");
    if (!file.is_open()) {
        printf("Impossible to open the file !\n");
        return Object(vector<Vertex>(), vector<Face>());
    }
    vector<Vertex> vertices;
    vector<Face> faces;
    while (!file.eof()) {
        string lineHeader;
        file >> lineHeader;
        if (lineHeader == "v") {
            float x, y, z;
            file >> x >> y >> z;
            float normal[3] = {0, 0, 0};
            Vertex vertex = Vertex(x, y, z, normal);
            vertices.push_back(vertex);
        }else if (lineHeader == "vn"){
            for (int i = 0; lineHeader == "vn" && i < vertices.size(); i++) {
                float x, y, z;
                file >> x >> y >> z;
                vertices.at(i).normal[0] = x;
                vertices.at(i).normal[1] = y;
                vertices.at(i).normal[2] = z;
                file >> lineHeader;
            }
        }else if (lineHeader == "f"){
            int x, y, z;
            file >> x >> y >> z;
            vector<Vertex> faceVertices;
            faceVertices.push_back(vertices[x - 1]);
            faceVertices.push_back(vertices[y - 1]);
            faceVertices.push_back(vertices[z - 1]);
            Face face = Face(faceVertices);
            faces.push_back(face);
        }
    }
    file.close();
    Object loadedObject(vertices, faces);
    return Object(vertices, faces);
}
