//
// Created by User on 01.11.2022.
//

#include "House.h"

void House::setupTriangles() {
    vertices = {
            {0.0f,   0.0f}, // 0
            {25.0f,  0.0f}, // 1
            {25.0f,  100.0f}, // 2
            {0.0f,   100.0f}, // 3
            {150.0f, 0.0f}, // 4
            {150.0f, 100.0f}, // 5
            {0.0f,   110.0f}, // 6
            {150.0f, 110.0f}, // 7
            {30.0f,  145.0f}, // 8
            {50.0f,  145.0f}, // 9
            {120.0f, 145.0f}, // 10
            {30.0f,  160.0f}, // 11
            {50.0f,  160.0f}, // 12
            {30.0f,  168.0f}, // 13
            {50.0f,  168.0f}, // 14
            {30.0f,  50.0f}, // 15
            {55.0f,  50.0f}, // 16
            {30.0f,  75.0f}, // 17
            {55.0f,  75.0f}, // 18
            {115.0f, 50.0f}, // 19
            {140.0f, 50.0f}, // 20
            {115.0f, 75.0f}, // 21
            {140.0f, 75.0f}, // 22
            {60.0f,  0.0f}, // 23
            {63.0f,  0.0f}, // 24
            {60.0f,  50.0f}, // 25
            {63.0f,  47.0f}, // 26
            {100.0f, 50.0f}, // 27
            {97.0f,  47.0f}, // 28
            {97.0f,  0.0f}, // 29
            {100.0f, 0.0f}, // 30
            {93.0f,  23.0f}, // 31
            {95.0f,  23.0f}, // 32
            {93.0f,  25.0f}, // 33
            {95.0f,  25.0f}, // 34
    };
    triangleVertices = {
            4,
            {
                    // Side-wall
                    vertices[0], vertices[1], vertices[3],
                    vertices[1], vertices[3], vertices[2],
                    // Wall
                    vertices[1], vertices[2], vertices[4],
                    vertices[2], vertices[4], vertices[5],
                    // Roof gutter
                    vertices[3], vertices[5], vertices[6],
                    vertices[5], vertices[6], vertices[7],
                    // Roof
                    vertices[6], vertices[7], vertices[8],
                    vertices[7], vertices[8], vertices[9],
                    vertices[7], vertices[9], vertices[10],
                    vertices[8], vertices[9], vertices[11],
                    vertices[9], vertices[11], vertices[12],
                    vertices[11], vertices[12], vertices[13],
                    vertices[12], vertices[13], vertices[14],
                    // Window-left
                    vertices[15], vertices[16], vertices[17],
                    vertices[16], vertices[17], vertices[18],
                    // Window-right
                    vertices[19], vertices[20], vertices[21],
                    vertices[20], vertices[21], vertices[22],
                    // Door-frame
                    vertices[23], vertices[24], vertices[25],
                    vertices[24], vertices[25], vertices[26],
                    vertices[25], vertices[26], vertices[27],
                    vertices[26], vertices[27], vertices[28],
                    vertices[27], vertices[28], vertices[30],
                    vertices[28], vertices[29], vertices[30],
                    // Door
                    vertices[24], vertices[29], vertices[26],
                    vertices[29], vertices[26], vertices[28],
                    // Door knob
                    vertices[31], vertices[32], vertices[33],
                    vertices[32], vertices[33], vertices[34],
            }
    };
    triangleVerticesColors = {
            4, {
                    // Side-wall
                    sideWallColor, sideWallColor, sideWallColor,
                    sideWallColor, sideWallColor, sideWallColor,
                    // Wall
                    wallColor, wallColor, wallColor,
                    wallColor, wallColor, wallColor,
                    // Roof gutter
                    roofGutterColor, roofGutterColor, roofGutterColor,
                    roofGutterColor, roofGutterColor, roofGutterColor,
                    // Roof
                    roofColor, roofColor, roofColor,
                    roofColor, roofColor, roofColor,
                    roofColor, roofColor, roofColor,
                    roofColor, roofColor, roofColor,
                    roofColor, roofColor, roofColor,
                    roofGutterColor, roofGutterColor, roofGutterColor,
                    roofGutterColor, roofGutterColor, roofGutterColor,
                    // Window-left
                    windowColor, windowColor, windowColor,
                    windowColor, windowColor, windowColor,
                    // Window-right
                    windowColor, windowColor, windowColor,
                    windowColor, windowColor, windowColor,
                    // Door-frame
                    doorFrameColor, doorFrameColor, doorFrameColor,
                    doorFrameColor, doorFrameColor, doorFrameColor,
                    doorFrameColor, doorFrameColor, doorFrameColor,
                    doorFrameColor, doorFrameColor, doorFrameColor,
                    doorFrameColor, doorFrameColor, doorFrameColor,
                    doorFrameColor, doorFrameColor, doorFrameColor,
                    // Door
                    doorColor, doorColor, doorColor,
                    doorColor, doorColor, doorColor,
                    // Door knob
                    doorKnobColor, doorKnobColor, doorKnobColor,
                    doorKnobColor, doorKnobColor, doorKnobColor,
            }
    };
}

House::House(float centerX, float centerY, float scale, bool flip) :
        Drawable(centerX, centerY, scale, scale, flip) {
    setupTriangles();
    setupVao();
}
