#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>

using namespace std;

struct object{
	vector<struct vertex> vertices;
	vector<struct vertex> verticesNormals;
	vector<struct face> faces;
};

struct vertex{
	float x;
	float y;
	float z;
};

struct face{
	int v1;
	int v2;
	int v3;
};
#endif
