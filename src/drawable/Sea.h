#ifndef GC_SEA_H
#define GC_SEA_H


#include "Drawable.h"
#include "../utils/color/Color.h"

class Sea : public Drawable {
private:
    Color darkBlue = Color::fromHex("#68ADC3");
    Color mediumBlue = Color::fromHex("#70B8C6");
    Color lightBlue = Color::fromHex("#85C9CC");

    bool increaseHeight = true;

    void setupShape() final override {
        vertices = {
                {0.0f,    0.0f}, // 0
                {1280.0f, 0.0f}, // 1
                {1280.0f, 65.0f}, // 2
                {0.0f,    65.0f}, // 3
                {1280.0f, 130.0f}, // 4
                {0.0f,    130.0f}, // 5
                {1280.0f, 195.0f}, // 6
                {0.0f,    195.0f}, // 7
        };
        triangleVertices = {
                4,
                {
                        vertices[0], vertices[1], vertices[2],
                        vertices[0], vertices[2], vertices[3],
                        vertices[3], vertices[2], vertices[4],
                        vertices[3], vertices[4], vertices[5],
                        vertices[4], vertices[5], vertices[6],
                        vertices[5], vertices[6], vertices[7],
                }
        };
        triangleVerticesColors = {
                4,
                {
                        lightBlue, lightBlue, lightBlue,
                        lightBlue, lightBlue, lightBlue,
                        mediumBlue, mediumBlue, mediumBlue,
                        mediumBlue, mediumBlue, mediumBlue,
                        darkBlue, darkBlue, darkBlue,
                        darkBlue, darkBlue, darkBlue,
                }
        };
    }

public:
    Sea() {
        setupShape();
        setupVao();
    }

    void stepAnimation() override {
        if (increaseHeight) {
            scale.y += 0.0015f;
            if (scale.y >= 1.1f) {
                increaseHeight = false;
            }
        } else {
            scale.y -= 0.0015f;
            if (scale.y <= 1.0f) {
                increaseHeight = true;
            }
        }
    }
};


#endif //GC_SEA_H
