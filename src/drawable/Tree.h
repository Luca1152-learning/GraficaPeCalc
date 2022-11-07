#ifndef GC_TREE_H
#define GC_TREE_H


#include "Drawable.h"
#include "../utils/color/Color.h"

class Tree : public Drawable {
private:
    Color trunkColor = Color::fromHex("#AE7961");
    Color darkGreenColor = Color::fromHex("#56AF82");
    Color lightGreenColor = Color::fromHex("#5FC08C");

    void setupShape() final override {
        vertices = {
                {70.0f,  0.0f}, // 0
                {80.0f,  0.0f}, // 1
                {80.0f,  80.0f}, // 2
                {70.0f,  80.0f}, // 3
                {0.0f,   80.0f}, // 4
                {75.0f,  80.0f}, // 5
                {75.0f,  320.0f}, // 6
                {150.0f, 80.0f}, // 7
        };
        triangleVertices = {
                4,
                {
                        // Trunk
                        vertices[0], vertices[1], vertices[3],
                        vertices[1], vertices[3], vertices[2],
                        // Left triangle
                        vertices[4], vertices[5], vertices[6],
                        // Right triangle
                        vertices[5], vertices[6], vertices[7],
                }
        };
        triangleVerticesColors = {
                4, {
                        // Trunk
                        trunkColor, trunkColor, trunkColor,
                        trunkColor, trunkColor, trunkColor,
                        // Left triangle
                        darkGreenColor, darkGreenColor, darkGreenColor,
                        // Right triangle
                        lightGreenColor, lightGreenColor, lightGreenColor,
                }
        };
    }

public:
    Tree(vec2 center, float scale = 1.0f) : Drawable(center.x, center.y, scale, scale) {
        setupShape();
        setupVao();
    }
};


#endif //GC_TREE_H
