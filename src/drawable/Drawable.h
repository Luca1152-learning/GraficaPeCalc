#ifndef GC_DRAWABLE_H
#define GC_DRAWABLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../utils/math/Vector.h"
#include "../utils/math/Matrix.h"
#include "../utils/Constants.h"
#include <iostream>

using namespace std;

class Drawable {
protected:
    vector<Vector> vertices;
    Matrix triangleVertices;
    Matrix triangleVerticesColors;

    vec2 translate;
    vec2 centerOfRotation;
    float rotationAround00Deg = 0.0f, rotationAroundCenterDeg = 0.0f;
    vec2 scale;
    bool flip;

    GLuint vao, verticesVbo, colorsVbo;

    void setupVao();

    virtual void setupTriangles() = 0;

public:
    Drawable(float translateX, float translateY, float scaleX = 1.0f, float scaleY = 1.0f, bool flip = false);

    void setCenterOfRotation(float centerX, float centerY) {
        centerOfRotation = {centerX, centerY};
    }

    virtual void render();
};


#endif //GC_DRAWABLE_H
