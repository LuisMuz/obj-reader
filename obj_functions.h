#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "class.h"

vector<Object> objects;

void loadOBJ(const string& filename) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo OBJ." << endl;
        return;
    }

    Object obj;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        iss >> token;

        if (token == "v") {
            Vertex vertex;
            if (iss >> vertex.x >> vertex.y >> vertex.z) {
                obj.vertices.push_back(vertex);
            }
            else {
                cout << "Error al leer vértice en línea: " << line << endl;
            }
        }
        else if (token == "vt") {
            TextureCoord texCoord;
            if (iss >> texCoord.u >> texCoord.v) {
                obj.texCoords.push_back(texCoord);
            }
            else {
                cout << "Error al leer coordenada de textura en línea: " << line << endl;
            }
        }
        else if (token == "vn") {
            Normal normal;
            if (iss >> normal.nx >> normal.ny >> normal.nz) {
                obj.normals.push_back(normal);
            }
            else {
                cout << "Error al leer normal en línea: " << line << endl;
            }
        }
        else if (token == "f") {
            Face face;
            string vertexInfo;
            while (iss >> vertexInfo) {
                istringstream vertexStream(vertexInfo);
                string vertexIndexStr, texIndexStr, normIndexStr;
                getline(vertexStream, vertexIndexStr, '/');
                getline(vertexStream, texIndexStr, '/');
                getline(vertexStream, normIndexStr, '/');

                if (!vertexIndexStr.empty() && !texIndexStr.empty() && !normIndexStr.empty()) {
                    int vertexIndex = stoi(vertexIndexStr) - 1;
                    int texIndex = stoi(texIndexStr) - 1;
                    int normIndex = stoi(normIndexStr) - 1;

                    face.vertexIndices.push_back(vertexIndex);
                    face.textureIndices.push_back(texIndex);
                    face.normalIndices.push_back(normIndex);
                }
                else {
                    cout << "Error al leer índices en línea: " << line << endl;
                }
            }
            obj.faces.push_back(face);
        }
        else {
            continue;
        }
    }
    objects.push_back(obj);
    file.close();
}

void printObject(const Object& obj) {
    cout << "Vertices:" << endl;
    for (const Vertex& vertex : obj.vertices) {
        cout << "  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << endl;
    }

    cout << "Coordenadas de Textura:" << endl;
    for (const TextureCoord& texCoord : obj.texCoords) {
        cout << "  (" << texCoord.u << ", " << texCoord.v << ")" << endl;
    }

    cout << "Normales:" << endl;
    for (const Normal& normal : obj.normals) {
        cout << "  (" << normal.nx << ", " << normal.ny << ", " << normal.nz << ")" << endl;
    }

    cout << "Caras:" << endl;
    for (const Face& face : obj.faces) {
        cout << "  Face:" << endl;
        for (size_t i = 0; i < face.vertexIndices.size(); ++i) {
            cout << "    Vertex Index: " << face.vertexIndices[i] << ", ";
            cout << "Texture Index: " << face.textureIndices[i] << ", ";
            cout << "Normal Index: " << face.normalIndices[i] << endl;
        }
    }
}
