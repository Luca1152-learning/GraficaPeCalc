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
        sunRays.push_back(new SunRay(400.0f, 400.0f, color));
    }

public:
    SunRays(int centerX, int centerY, Color color) : Drawable(centerX, centerY), color(color) {
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
