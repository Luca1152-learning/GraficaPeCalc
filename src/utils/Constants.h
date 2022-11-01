#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

using namespace glm;

static mat4 RESIZE_MATRIX = ortho(-400.0f, 400.0f, -80.0f, 400.0f);