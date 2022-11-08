#include "Tree.h"

void Tree::setupShape() {
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

Tree::Tree(vec2 center, float scale) : Drawable(center.x, center.y, scale, scale) {
    setupShape();
    setupVao();
}
