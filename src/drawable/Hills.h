#ifndef GC_HILLS_H
#define GC_HILLS_H

#include "Drawable.h"
#include "../utils/color/Color.h"

class Hills : public Drawable {
private:
    Color lightGreen = Color::fromHex("#9DCE58");
    Color darkGreen = Color::fromHex("#92BF48");

    void setupShape() final override {
        vertices = {
                {0.0f, 0.0f}, // 0
                {0.0f, 65.0f}, // 1
                {70.0f, 100.0f}, // 2
                {130.0f, 130.0f}, // 3
                {180.0f, 140.0f}, // 4
                {240.0f, 135.0f}, // 5
                {282.0f, 111.0f}, // 6
                {334.0f, 78.0f}, // 7
                {380.0f, 49.0f}, // 8
                {423.0f, 0.0f}, // 9
        };
        triangleVertices = {
                4,
                {
                        vertices[0], vertices[1], vertices[2],
                        vertices[0], vertices[2], vertices[3],
                        vertices[0], vertices[3], vertices[4],
                        vertices[0], vertices[4], vertices[5],
                        vertices[0], vertices[5], vertices[6],
                        vertices[0], vertices[6], vertices[7],
                        vertices[0], vertices[7], vertices[8],
                        vertices[0], vertices[8], vertices[9],
                }
        };
        triangleVerticesColors = {
                4,
                {
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                }
        };
    }

public:
    Hills() : Drawable(0.0f, 190.0f, 1.0f, 1.0f) {
        setupShape();
        setupVao();
    }
};


#endif //GC_HILLS_H
