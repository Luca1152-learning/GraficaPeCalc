#ifndef GC_MATRIX_H
#define GC_MATRIX_H

#include "Vector.h"
#include <vector>

using namespace std;

class Matrix {
private:
    int vectorLength;
    vector<Vector> vectors;

public:
    Matrix(int vectorLength = 0, vector<Vector> vectors = {}) : vectorLength(vectorLength), vectors(vectors) {
    }

    int getSize() {
        return vectors.size();
    }

    float *toCArray() {
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
};


#endif //GC_MATRIX_H
