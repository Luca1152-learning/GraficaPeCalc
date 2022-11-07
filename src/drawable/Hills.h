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
                {0.0f,    0.0f}, // 0
                {0.0f,    65.0f}, // 1
                {70.0f,   100.0f}, // 2
                {130.0f,  130.0f}, // 3
                {180.0f,  140.0f}, // 4
                {240.0f,  135.0f}, // 5
                {282.0f,  111.0f}, // 6
                {334.0f,  78.0f}, // 7
                {380.0f,  49.0f}, // 8
                {423.0f,  0.0f}, // 9
                {350.0f,  120.0f}, // 10
                {396.0f,  120.0f}, // 11
                {440.0f,  112.0f}, // 12
                {430.0f,  61.0f}, // 13
                {398.0f,  27.0f}, // 14
                {480.0f,  95.0f}, // 15
                {540.0f,  126.0f}, // 16
                {580.0f,  158.0f}, // 17
                {645.0f,  178.0f}, // 18
                {708.0f,  193.0f}, // 19
                {785.0f,  183.0f}, // 20
                {833.0f,  176.0f}, // 21
                {895.0f,  150.0f}, // 22
                {950.0f,  120.0f}, // 23
                {1020.0f, 80.0f}, // 24
                {1070.0f, 44.0f}, // 25
                {1090.0f, 0.0f}, // 26
                {965.0f,  110.0f}, // 27
                {1030.0f, 117.0f}, // 28
                {1066.0f, 125.0f}, // 29
                {1128.0f, 113.0f}, // 30
                {1230.0f, 88.0f}, // 31
                {1280.0f, 64.0f}, // 32
                {1280.0f, 0.0f}, // 33
        };
        triangleVertices = {
                4,
                {
                        // Hill 1
                        vertices[0], vertices[1], vertices[2],
                        vertices[0], vertices[2], vertices[3],
                        vertices[0], vertices[3], vertices[4],
                        vertices[0], vertices[4], vertices[5],
                        vertices[0], vertices[5], vertices[6],
                        vertices[0], vertices[6], vertices[7],
                        vertices[0], vertices[7], vertices[8],
                        vertices[0], vertices[8], vertices[9],
                        // Hill 2
                        vertices[6], vertices[7], vertices[10],
                        vertices[7], vertices[10], vertices[11],
                        vertices[7], vertices[8], vertices[11],
                        vertices[8], vertices[11], vertices[12],
                        vertices[8], vertices[12], vertices[14],
                        vertices[12], vertices[14], vertices[13],
                        // Hill 3
                        vertices[12], vertices[13], vertices[15],
                        vertices[14], vertices[13], vertices[9],
                        vertices[9], vertices[13], vertices[15],
                        vertices[9], vertices[15], vertices[16],
                        vertices[9], vertices[16], vertices[17],
                        vertices[9], vertices[17], vertices[18],
                        vertices[9], vertices[18], vertices[19],
                        vertices[9], vertices[19], vertices[20],
                        vertices[9], vertices[20], vertices[21],
                        vertices[9], vertices[21], vertices[22],
                        vertices[9], vertices[22], vertices[23],
                        vertices[9], vertices[23], vertices[24],
                        vertices[9], vertices[24], vertices[25],
                        vertices[9], vertices[25], vertices[26],
                        // Hill 4
                        vertices[27], vertices[24], vertices[28],
                        vertices[28], vertices[24], vertices[29],
                        vertices[24], vertices[29], vertices[25],
                        vertices[25], vertices[29], vertices[30],
                        vertices[25], vertices[26], vertices[30],
                        vertices[26], vertices[30], vertices[31],
                        vertices[26], vertices[31], vertices[32],
                        vertices[26], vertices[32], vertices[33],
                }
        };
        triangleVerticesColors = {
                4,
                {
                        // Hill 1
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        // Hill 2
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        // Hill 3
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        lightGreen, lightGreen, lightGreen,
                        // Hill 4
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
                        darkGreen, darkGreen, darkGreen,
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
