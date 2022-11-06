#ifndef GC_VECTOR_H
#define GC_VECTOR_H

#include <glm/vec3.hpp>

using namespace glm;

class Vector {
private:
    float x, y, z, u;

public:
    Vector(float x, float y, float z = 0.0f, float u = 1.0f);

    operator vec3();

    float getX() const;

    float getY() const;

    float getZ() const;

    float getU() const;
};


#endif //GC_VECTOR_H
