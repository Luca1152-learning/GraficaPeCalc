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

    void setupShape() final override;

public:
    Sun(float centerX, float centerY, float radius, Color color);

    void render() override;
};


#endif //GC_SUN_H
