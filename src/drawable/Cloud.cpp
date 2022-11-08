#include "Cloud.h"

void Cloud::setupShape() {
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

Cloud::Cloud(vec2 center, float width) : Drawable(), width(width) {
    translate = {center.x, center.y};
    setupShape();
    setupVao();
}

void Cloud::render() {
    Drawable::render();
    circleLeft->render();
    circleRight->render();
}

void Cloud::stepAnimation() {
    translate.x -= speed;
    circleLeft->setTranslate({translate.x + height / 2.0f, translate.y + height / 2.0f});
    circleRight->setTranslate({translate.x + width - height / 2.0f, translate.y + height / 2.0f});

    if (translate.x <= -width) {
        translate.x = 1280.0f;
    }
}
