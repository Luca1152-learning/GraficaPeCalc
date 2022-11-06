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
    Matrix(int vectorLength = 0, vector<Vector> vectors = {});

    Vector getCenter();

    int getSize();

    float *toCArray();
};


#endif //GC_MATRIX_H
