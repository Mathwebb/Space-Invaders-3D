#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include "../game_classes/Object.cpp"
using namespace std;

Object loadObject(const char *path) {
    fstream file(path);
    fstream debugFile("debug.txt", ios::out);
    if (!file.is_open()) {
        printf("Impossible to open the file !\n");
        return Object(vector<Vertex>(), vector<Face>());
    }
    vector<Vertex> vertices;
    vector<Face> faces;
    while (!file.eof()) {
        string lineHeader;
        if ((file >> lineHeader).fail()) break;
        if (lineHeader == "v") {
            float x, y, z;
            if ((file >> x >> y >> z).fail()) break;
            float normal[3] = {0, 0, 0};
            Vertex vertex = Vertex(x, y, z, normal);
            vertices.push_back(vertex);
            debugFile << "Vertex: " << x << " " << y << " " << z << endl;
        }else if (lineHeader == "vn"){
            for (unsigned int i = 0; lineHeader == "vn" && i < vertices.size(); i++) {
                float x, y, z;
                if ((file >> x >> y >> z).fail()) break;
                vertices.at(i).setNormal(x, y, z);
                debugFile << "Normal: " << x << " " << y << " " << z << endl;
                file >> lineHeader;
            }
        }else if (lineHeader == "f"){
            int v1, v2, v3;
            if ((file >> v1 >> v2 >> v3).fail()) break;
            Face face = Face(v1 - 1, v2 - 1, v3 - 1);
            faces.push_back(face);
            debugFile << "Face: " << v1 << " " << v2 << " " << v3 << endl;
        }
    }
    file.close();
    Object loadedObject(vertices, faces);
    return Object(vertices, faces);
}
