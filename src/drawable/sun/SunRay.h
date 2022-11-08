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

    void setupShape() final override;

public:
    SunRay(vec2 sunCenter, float sunRadius, float rotationDeg, Color color);

    void stepAnimation() override;
};


#endif //GC_SUNRAY_H
