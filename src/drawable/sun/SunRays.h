#ifndef GC_SUNRAYS_H
#define GC_SUNRAYS_H


#include "../Drawable.h"
#include "./SunRay.h"
#include "../../utils/color/Color.h"

class SunRays : public Drawable {
private:
    vec2 sunCenter;
    float sunRadius;
    Color color;

    vector<SunRay *> sunRays;

    void setupShape() final override {
        sunRays.push_back(new SunRay(sunCenter, sunRadius, 0.0f, color));
        sunRays.push_back(new SunRay(sunCenter, sunRadius, 45.0f, color));
        sunRays.push_back(new SunRay(sunCenter, sunRadius, 90.0f, color));
        sunRays.push_back(new SunRay(sunCenter, sunRadius, 135.0f, color));
        sunRays.push_back(new SunRay(sunCenter, sunRadius, 180.0f, color));
        sunRays.push_back(new SunRay(sunCenter, sunRadius, 270.0f, color));
        sunRays.push_back(new SunRay(sunCenter, sunRadius, 225.0f, color));
        sunRays.push_back(new SunRay(sunCenter, sunRadius, 315.0f, color));
    }

public:
    SunRays(vec2 sunCenter, float sunRadius, Color color) : sunCenter(sunCenter), sunRadius(sunRadius), color(color) {
        setupShape();
    }

    void render() override {
        Drawable::render();
        for (auto sunRay: sunRays) {
            sunRay->render();
        }
    }
};


#endif //GC_SUNRAYS_H
