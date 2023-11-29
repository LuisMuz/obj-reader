#pragma once
#include "class.h"

double dotProduct(vector<double> vector1, vector<double> vector2) {
    if (vector1.size() != vector2.size()) {
        throw invalid_argument("Los vectores deben tener la misma longitud.");
    }

    double result = 0.0;
    for (size_t i = 0; i < vector1.size(); ++i) {
        result += vector1[i] * vector2[i];
    }

    return result;
}

vector<double> crossProduct(vector<double> vector1, vector<double> vector2) {

    vector<double> result(3);
    result[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
    result[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
    result[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];

    return result;
}

vector<double> normalize(vector<double> vec) {
    double magnitude = 0.0;
    for (double component : vec) {
        magnitude += component * component;
    }

    magnitude = sqrt(magnitude);

    vector <double> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] / magnitude;
    }

    return result;
}

vector<double> subtractVectors(vector<double> vector1, vector<double> vector2) {
    if (vector1.size() != vector2.size()) {
        throw invalid_argument("Los vectores deben tener la misma longitud.");
    }

    vector<double> result(vector1.size());
    for (size_t i = 0; i < vector1.size(); ++i) {
        result[i] = vector1[i] - vector2[i];
    }

    return result;
}