#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GL/glew.h>

using namespace glm;

class Constants {
public:
    static const int WIDTH;
    static const int HEIGHT;

    // Matrices
    static const mat4 RESIZE_MATRIX;
    static GLuint MATRIX_LOCATION;
};