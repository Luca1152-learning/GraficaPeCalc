#include "Sun.h"

void Sun::setupShape() {
    circle = new Circle(center.x, center.y, radius, color);
    sunRays = new SunRays(center, radius, color);
}

Sun::Sun(float centerX, float centerY, float radius, Color color) :
        center(centerX, centerY), radius(radius), color(color) {
    setupShape();
    setupVao();
}

void Sun::render() {
    circle->render();
    sunRays->render();

    circle->stepAnimation();
    sunRays->stepAnimation();
}
