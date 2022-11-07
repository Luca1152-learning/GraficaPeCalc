#ifndef GC_SUNRAY_H
#define GC_SUNRAY_H


#include "../Drawable.h"
#include "../../utils/color/Color.h"

class SunRay : public Drawable {
private:
    vec2 sunCenter;
    float sunRadius, extraRadius = 0.0f;
    bool increaseRadius = true;

    Color color;

    void setupShape() final override {
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
    SunRay(vec2 sunCenter, float sunRadius, float rotationDeg, Color color) :
            Drawable(sunCenter.x - sunRadius, sunCenter.y - sunRadius),
            sunCenter(sunCenter), sunRadius(sunRadius), color(color) {
        setCenterOfRotation(sunRadius, sunRadius);
        rotationAroundCenterDeg = rotationDeg;
        rotationAround00Deg = 135.0f; // Fix rotation
        setupShape();
        setupVao();
    }

    void stepAnimation() override {
        rotationAroundCenterDeg += 0.15f;
        if (rotationAroundCenterDeg > 360.0f) {
            rotationAroundCenterDeg = 0.0f;
        }

        if (increaseRadius) {
            extraRadius += 0.07f;
            if (extraRadius >= 5.0f) {
                increaseRadius = false;
            }
        } else {
            extraRadius -= 0.07f;
            if (extraRadius <= 0.0f) {
                increaseRadius = true;
            }
        };
        setCenterOfRotation(sunRadius + extraRadius, sunRadius + extraRadius);
        translate = {sunCenter.x - sunRadius - extraRadius, sunCenter.y - sunRadius - extraRadius};
    }
};


#endif //GC_SUNRAY_H
