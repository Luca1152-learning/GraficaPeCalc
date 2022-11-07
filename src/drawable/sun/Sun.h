#ifndef GC_SUN_H
#define GC_SUN_H


#include "../Drawable.h"
#include "../Circle.h"
#include "./SunRays.h"
#include "../../utils/color/Color.h"

class Sun : public Drawable {
private:
    vec2 center;
    float radius;
    Color color;

    Circle *circle;
    SunRays *sunRays;

    void setupShape() final override {
        circle = new Circle(center.x, center.y, radius, color);
        sunRays = new SunRays(center, radius, color);
    }

public:
    Sun(float centerX, float centerY, float radius, Color color) :
            center(centerX, centerY), radius(radius), color(color) {
        setupShape();
        setupVao();
    }

    void render() override {
        circle->render();
        sunRays->render();

        circle->stepAnimation();
        sunRays->stepAnimation();
    }
};


#endif //GC_SUN_H
