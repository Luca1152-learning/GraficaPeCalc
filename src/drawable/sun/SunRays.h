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

    void setupShape() final override;

public:
    SunRays(vec2 sunCenter, float sunRadius, Color color);

    void render() override;
};


#endif //GC_SUNRAYS_H
