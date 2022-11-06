#include "Matrix.h"

Matrix::Matrix(int vectorLength, vector<Vector> vectors) : vectorLength(vectorLength), vectors(vectors) {
}

int Matrix::getSize() {
    return vectors.size();
}

float *Matrix::toCArray() {
    vector<float> *floatVectors = new vector<float>();

    for (auto vector: vectors) {
        if (vectorLength >= 2) {
            floatVectors->push_back(vector.getX());
            floatVectors->push_back(vector.getY());
        }
        if (vectorLength >= 3) {
            floatVectors->push_back(vector.getZ());
        }
        if (vectorLength >= 4) {
            floatVectors->push_back(vector.getU());
        }
    }

    return floatVectors->data();
}

Vector Matrix::getCenter() {
    float minX = numeric_limits<float>::infinity();
    float minY = numeric_limits<float>::infinity();
    float minZ = numeric_limits<float>::infinity();
    float minU = numeric_limits<float>::infinity();

    float maxX = numeric_limits<float>::lowest();
    float maxY = numeric_limits<float>::lowest();
    float maxZ = numeric_limits<float>::lowest();
    float maxU = numeric_limits<float>::lowest();

    for (auto v: vectors) {
        minX = min(v.getX(), minX);
        minY = min(v.getY(), minY);
        minZ = min(v.getZ(), minZ);
        minU = min(v.getU(), minU);

        maxX = max(v.getX(), maxX);
        maxY = max(v.getY(), maxY);
        maxZ = max(v.getZ(), maxZ);
        maxU = max(v.getU(), maxU);
    }

    float medianX = (minX + maxX) / 2, medianY = (minY + maxY) / 2,
            medianZ = (minZ + maxZ) / 2, medianU = (minU + maxU) / 2;

    return Vector(medianX, medianY, medianZ, medianU);
}
