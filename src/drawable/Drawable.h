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

using namespace glm;
using namespace std;

class Drawable {
protected:
    vector<Vector> vertices;
    Matrix triangleVertices;
    Matrix triangleVerticesColors;

    float centerX, centerY, scaleX, scaleY;
    bool flip;

    GLuint vao, verticesVbo, colorsVbo;

    void setupVao();

    virtual void setupTriangles() = 0;

public:
    Drawable(float centerX, float centerY, float scaleX = 1.0f, float scaleY = 1.0f, bool flip = false);

    virtual void render();
};


#endif //GC_DRAWABLE_H
