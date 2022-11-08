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

    void setupShape() final override {
        // Circles
        circleLeft = new Circle(translate.x + height / 2.0f, translate.y + height / 2.0f, height / 2.0f, color);
        circleRight = new Circle(translate.x + width - height / 2.0f, translate.y + height / 2.0f, height / 2.0f,
                                 color);

        // Connecting the two circles
        vertices = {
                {0.0f + height / 2.0f,  0.0f}, // 0
                {width - height / 2.0f, 0.0f}, // 1
                {width - height / 2.0f, height}, // 2
                {0 + height / 2.0f,     height}, // 3
        };
        triangleVertices = {
                4,
                {
                        vertices[0], vertices[1], vertices[2],
                        vertices[0], vertices[2], vertices[3],
                }
        };
        triangleVerticesColors = {
                4,
                {
                        color, color, color,
                        color, color, color,
                }
        };
    }

public:
    Cloud(vec2 center, float width) : Drawable(), width(width) {
        translate = {center.x, center.y};
        setupShape();
        setupVao();
    }

    void render() override {
        Drawable::render();
        circleLeft->render();
        circleRight->render();
    }

    void stepAnimation() override {
        translate.x -= speed;
        circleLeft->setTranslate({translate.x + height / 2.0f, translate.y + height / 2.0f});
        circleRight->setTranslate({translate.x + width - height / 2.0f, translate.y + height / 2.0f});

        if (translate.x <= -width) {
            translate.x = 1280.0f;
        }
    }
};


#endif //GC_CLOUD_H
