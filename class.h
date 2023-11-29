#pragma once
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <thread>
#include <cmath>
#include <corecrt_math_defines.h>

using namespace std;

class Vertex {
public:
    float x, y, z;
    
    Vertex(double a, double b, double c) {
        x = a;
        y = b;
        z = c;
    }

    Vertex() {};
};

class TextureCoord {
public:
    double u, v;
};


class Normal {
public:
    double nx, ny, nz;
};

class Face {
public:
    vector<int> vertexIndices;
    vector<int> textureIndices;
    vector<int> normalIndices;
};

class Object {
public:
    vector<Vertex> vertices;
    vector<TextureCoord> texCoords;
    vector<Normal> normals;
    vector<Face> faces;
};