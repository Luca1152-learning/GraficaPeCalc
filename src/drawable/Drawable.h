#ifndef GC_DRAWABLE_H
#define GC_DRAWABLE_H


#include <GL/glew.h>

class Drawable {
protected:
    GLuint vao, verticesVbo, colorsVbo;

public:
    virtual void initialize() = 0;

    virtual void render() = 0;
};


#endif //GC_DRAWABLE_H
