#ifndef GC_SUNRAY_H
#define GC_SUNRAY_H


#include "../Drawable.h"
#include "../../utils/color/Color.h"

class SunRay : public Drawable {
private:
    Color color;

    void setupTriangles() final override {
        vertices = {
                {0.0f, 0.0f}, // 0
                {15.0f, 0.0f}, // 1
                {7.5f, 20.0f} // 2
        };
        triangleVertices = {
                4,
                {vertices[0], vertices[1], vertices[2]}
        };
        triangleVerticesColors = {
                4,
                {color, color, color}
        };
    }

public:
    SunRay(float centerX, float centerY, Color color) : Drawable(centerX, centerY), color(color) {
        setupTriangles();
        setupVao();
    }
};


#endif //GC_SUNRAY_H
