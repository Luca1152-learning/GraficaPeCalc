#ifndef GC_CONSTANTS_H
#define GC_CONSTANTS_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GL/glew.h>

using namespace glm;

class Constants {
public:
    // Window
    static const int WIDTH;
    static const int HEIGHT;

    // Matrices
    static const mat4 RESIZE_MATRIX;
    static GLuint MATRIX_LOCATION;
};

#endif //GC_CONSTANTS_H