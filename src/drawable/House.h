//
// Created by User on 01.11.2022.
//

#ifndef GC_HOUSE_H
#define GC_HOUSE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../utils/ShadersUtils.h"
#include "../utils/Color.h"
#include "../utils/Constants.h"
#include "Drawable.h"
#include <vector>
#include "../utils/Vector.h"
#include "../utils/Matrix.h"

using namespace std;

class House : public Drawable {
private:
    Color sideWallColor = Color::fromHex("#DEDCDA");
    Color wallColor = Color::fromHex("#E9E7E8");
    Color roofGutterColor = Color::fromHex("#7C292E");
    Color roofColor = Color::fromHex("#BA4C40");
    Color windowColor = Color::fromHex("#458592");
    Color doorColor = Color::fromHex("#C5A671");
    Color doorFrameColor = Color::fromHex("#966D44");
    Color doorKnobColor = Color::fromHex("#EFCF9D");

    vector<Vector> vertices;
    Matrix triangleVertices;
    Matrix triangleVerticesColors;

    float centerX, centerY, scaleX, scaleY;
    bool flip;
    const vec3 DRAWABLE_CENTER = vec3(75.0f, 80.0f, 0.0f);

    void initialize() final {
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

        // Bind VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Vertices VBO
        float *triangleVerticesCArray = triangleVertices.toCArray();
        glGenBuffers(1, &verticesVbo);
        glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float) * triangleVertices.getSize(), triangleVerticesCArray,
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // Colors VBO
        float *triangleVerticesColorsCArray = triangleVerticesColors.toCArray();
        glGenBuffers(1, &colorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float) * triangleVertices.getSize(), triangleVerticesColorsCArray,
                     GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

        // Clear VAO
        glBindVertexArray(0);
    }

public:
    House(
            float centerX, float centerY, float scale, bool flip
    ) : centerX(centerX), centerY(centerY), scaleX(scale), scaleY(scale), flip(flip) {
        initialize();
    }

    void render() {
        mat4 resizeMatrix = Constants::RESIZE_MATRIX;
        mat4 translateTo00Matrix = translate(mat4(1.0f), -DRAWABLE_CENTER);
        mat4 translateToXYMatrix = translate(mat4(1.0f), vec3(centerX, centerY, 0.0f));
        mat4 scaleMatrix = scale(mat4(1.0f), vec3(scaleX, scaleY, 0.0f));
        mat4 flipMatrix = flip ? rotate(mat4(1.0f), radians(180.0f), vec3(0.0f, 1.0f, 0.0f)) : mat4(1.0f);
        mat4 resultingMatrix = resizeMatrix * translateToXYMatrix * scaleMatrix * flipMatrix * translateTo00Matrix;

        glUniformMatrix4fv(Constants::MATRIX_LOCATION, 1, GL_FALSE, &resultingMatrix[0][0]);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, triangleVertices.getSize());
        glBindVertexArray(0);
    }
};


#endif //GC_HOUSE_H
