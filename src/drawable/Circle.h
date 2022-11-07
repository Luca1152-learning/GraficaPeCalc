#ifndef GC_CIRCLE_H
#define GC_CIRCLE_H


#include "Drawable.h"
#include "../utils/color/Color.h"

using namespace glm;

class Circle : public Drawable {
private:
    Color color;

    void setupShape() final override;

public:
    Circle(float centerX, float centerY, float radius, Color color);
};


#endif //GC_CIRCLE_H
