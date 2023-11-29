#pragma once
#include "class.h"

double t = 0.02;
double totalPos = 1.0 / t;
vector<vector<double>> rotMatrix;
vector <vector <double>> matrix;

vector <vector <double>> matrixBezier(double t) {
    Vertex pointA{ 22.47, -8.9, -1.0 };
    Vertex pointB{ 0.64, -16, -1.0 };
    Vertex pointC{ 6.7, 11.6, -1.0 };
    Vertex pointD{ -12.6, -5.6, -1.0 };
    double tm = 1 - t;

    double x = (pow(tm, 3) * pointA.x) + (3 * t * pow(tm, 2) * pointB.x) + (3 * pow(t, 2) * tm * pointC.x) + (pow(t, 3) * pointD.x);
    double y = (pow(tm, 3) * pointA.y) + (3 * t * pow(tm, 2) * pointB.y) + (3 * pow(t, 2) * tm * pointC.y) + (pow(t, 3) * pointD.y);
    double z = (pow(tm, 3) * pointA.z) + (3 * t * pow(tm, 2) * pointB.z) + (3 * pow(t, 2) * tm * pointC.z) + (pow(t, 3) * pointD.z);

    matrix = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };

    return matrix;
}

vector <double> multiplyMatrix(vector <vector <double>> mat, double x, double y, double z) {
    vector<double> matR = {
        {mat[0][3] + x},
        {mat[1][3] + y},
        {mat[2][3] + z}
    };

    return matR;
}

vector <vector <double>> matrixRotated(double r) {
    double angle = r * M_PI / 180.0 * 360;

    rotMatrix = {
        {cos(angle), 0, sin(angle), 0},
        {0, 1, 0, 0},
        {-sin(angle), 0, cos(angle), 0},
        {0, 0, 0, 1}
    };

    return rotMatrix;
}

vector<double> resMatrixRotated(vector<double> matCoor, vector <vector <double>> matrix) {

    int row_mat1 = matrix.size();
    int column_mat1 = matrix[0].size();
    int row_mat2 = matCoor.size();

    vector<double> res(row_mat1, 0.0);

    for (int i = 0; i < row_mat1; i++) {
        for (int k = 0; k < column_mat1; k++) {
            res[i] += matrix[i][k] * matCoor[k];
        }
    }

    return res;
}