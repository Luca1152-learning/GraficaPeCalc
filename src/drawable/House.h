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

    void initialize() final {
        vector<Vector> vertices = {
                {0.0f,  0.0f},
                {25.0f, 0.0f},
                {25.0f, 100.0f},
                {0.0f,  100.0f},
        };
        Matrix triangleVertices = {
                2,
                {
                        vertices[0], vertices[1], vertices[3],
                        vertices[1], vertices[3], vertices[2],
                }
        };

        Matrix triangleVerticesColors = {
                4, {
                        sideWallColor, sideWallColor, sideWallColor,
                        sideWallColor, sideWallColor, sideWallColor,
                }
        };

        // Bind VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Vertices VBO
        float *triangleVerticesCArray = triangleVertices.toCArray();
        glGenBuffers(1, &verticesVbo);
        glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * sizeof(triangleVerticesCArray), triangleVerticesCArray,
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // Colors VBO
        float *triangleVerticesColorsCArray = triangleVerticesColors.toCArray();
        glGenBuffers(1, &colorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * sizeof(triangleVerticesColorsCArray),
                     triangleVerticesColorsCArray, GL_STATIC_DRAW);
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
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
};


#endif //GC_HOUSE_H
