#include "Vector.h"

Vector::Vector(float x, float y, float z, float u) : x(x), y(y), z(z), u(u) {}

float Vector::getX() const {
    return x;
}

float Vector::getY() const {
    return y;
}

float Vector::getZ() const {
    return z;
}

float Vector::getU() const {
    return u;
}

Vector::operator vec3() {
    return vec3(x, y, z);
}
