#ifndef GC_CLOUD_H
#define GC_CLOUD_H


#include "Drawable.h"
#include "Circle.h"
#include "../utils/color/Color.h"

class Cloud : public Drawable {
private:
    Color color = Color::fromHex("#E1F3F6", 0.8f);
    const float height = 50.0f;
    const float speed = 0.5f;
    float width;

    Circle *circleLeft;
    Circle *circleRight;

    void setupShape() final override;

public:
    Cloud(vec2 center, float width);

    void render() override;

    void stepAnimation() override;
};


#endif //GC_CLOUD_H
