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

    vector<Vector> vertices;
    Matrix triangleVertices;
    Matrix triangleVerticesColors;

    void initialize() final {
        vertices = {
                {0.0f,   0.0f}, // 0
                {25.0f,  0.0f}, // 1
                {25.0f,  100.0f}, // 2
                {0.0f,   100.0f}, // 3
                {150.0f, 0.0f}, // 4
                {150.0f, 100.0f}, // 5
        };
        triangleVertices = {
                2,
                {
                        // Side-wall
                        vertices[0], vertices[1], vertices[3],
                        vertices[1], vertices[3], vertices[2],
                        // Wall
                        vertices[1], vertices[2], vertices[4],
                        vertices[2], vertices[4], vertices[5],
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
                }
        };

        // Bind VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Vertices VBO
        float *triangleVerticesCArray = triangleVertices.toCArray();
        glGenBuffers(1, &verticesVbo);
        glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
        glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * triangleVertices.getSize(), triangleVerticesCArray,
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
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
    House() {
        initialize();
    }

    void render() {
        mat4 resizeMatrix = Constants::RESIZE_MATRIX;
        glUniformMatrix4fv(Constants::MATRIX_LOCATION, 1, GL_FALSE, &resizeMatrix[0][0]);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, triangleVertices.getSize());
        glBindVertexArray(0);
    }
};


#endif //GC_HOUSE_H
