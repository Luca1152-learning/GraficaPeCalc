#include "SunRays.h"

void SunRays::setupShape() {
    sunRays.push_back(new SunRay(sunCenter, sunRadius, 0.0f, color));
    sunRays.push_back(new SunRay(sunCenter, sunRadius, 45.0f, color));
    sunRays.push_back(new SunRay(sunCenter, sunRadius, 90.0f, color));
    sunRays.push_back(new SunRay(sunCenter, sunRadius, 135.0f, color));
    sunRays.push_back(new SunRay(sunCenter, sunRadius, 180.0f, color));
    sunRays.push_back(new SunRay(sunCenter, sunRadius, 270.0f, color));
    sunRays.push_back(new SunRay(sunCenter, sunRadius, 225.0f, color));
    sunRays.push_back(new SunRay(sunCenter, sunRadius, 315.0f, color));
}

SunRays::SunRays(vec2 sunCenter, float sunRadius, Color color) : sunCenter(sunCenter), sunRadius(sunRadius), color(color) {
    setupShape();
}

void SunRays::render() {
    Drawable::render();
    for (auto sunRay: sunRays) {
        sunRay->render();
    }
    for (auto sunRay: sunRays) {
        sunRay->stepAnimation();
    }
}
