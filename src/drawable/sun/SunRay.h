#ifndef GC_SUNRAY_H
#define GC_SUNRAY_H


#include "../Drawable.h"
#include "../../utils/color/Color.h"

class SunRay : public Drawable {
private:
    Color color;
    float sunCenterX, sunCenterY;

    void setupTriangles() final override {
        vertices = {
                {0.0f,  0.0f}, // 0
                {15.0f, 0.0f}, // 1
                {7.5f,  20.0f} // 2
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
    SunRay(float sunCenterX, float sunCenterY, float rotationDeg, Color color) :
            Drawable(500.0f, 500.0f), sunCenterX(sunCenterX), sunCenterY(sunCenterY), color(color) {
        setCenterOfRotation(50.0f, 50.0f);
        this->rotationAroundCenterDeg = rotationDeg;
        rotationAround00Deg = 135.0f;
        setupTriangles();
        setupVao();
    }
};


#endif //GC_SUNRAY_H
