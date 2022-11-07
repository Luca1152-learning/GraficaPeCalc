#ifndef GC_SUNRAYS_H
#define GC_SUNRAYS_H


#include "../Drawable.h"
#include "./SunRay.h"
#include "../../utils/color/Color.h"

class SunRays : public Drawable {
private:
    vector<SunRay *> sunRays;
    Color color;

    void setupTriangles() final override {
        sunRays.push_back(new SunRay(translate[0], translate[1], 0.0f, color));
        sunRays.push_back(new SunRay(translate[0], translate[1], 45.0f, color));
        sunRays.push_back(new SunRay(translate[0], translate[1], 90.0f, color));
        sunRays.push_back(new SunRay(translate[0], translate[1], 135.0f, color));
        sunRays.push_back(new SunRay(translate[0], translate[1], 180.0f, color));
        sunRays.push_back(new SunRay(translate[0], translate[1], 270.0f, color));
        sunRays.push_back(new SunRay(translate[0], translate[1], 225.0f, color));
        sunRays.push_back(new SunRay(translate[0], translate[1], 315.0f, color));
    }

public:
    SunRays(int sunCenterX, int sunCenterY, Color color) : Drawable(100.0f, 100.0f), color(color) {
        setupTriangles();
        setupVao();
    }

    void render() override {
        Drawable::render();
        for (auto sunRay: sunRays) {
            sunRay->render();
        }
    }
};


#endif //GC_SUNRAYS_H
