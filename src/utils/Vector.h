#ifndef GC_VECTOR_H
#define GC_VECTOR_H

#include "Color.h"

class Vector {
private:
    float x, y, z, u;

public:
    Vector(float x, float y, float z = 0.0f, float u = 0.0f) : x(x), y(y), z(z), u(u) {};

    Vector(Color color) : x(color.getR()), y(color.getG()), z(color.getB()), u(color.getA()) {};

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getZ() const {
        return z;
    }

    float getU() const {
        return u;
    }
};


#endif //GC_VECTOR_H
