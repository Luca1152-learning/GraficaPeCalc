//
// Created by User on 01.11.2022.
//

#ifndef GC_HOUSE_H
#define GC_HOUSE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "utils/ShadersUtils.h"
#include "utils/Color.h"
#include "utils/Constants.h"

class House {
private:
    GLuint vboId, vaoId;

    Color wallColor = Color(255, 0, 255);
    Color roofColor = Color(255, 0, 0);
    Color doorColor = Color(255, 0, 255);

    void initialize() {
        float testTriangle[] = {
                -0.9f, -0.5f, 0.0f,  // left
                -0.0f, -0.5f, 0.0f,  // right
                -0.45f, 0.5f, 0.0f,  // top
        };

        glGenVertexArrays(1, &vaoId);
        glGenBuffers(1, &vboId);

        glBindVertexArray(vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(testTriangle), testTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

public:
    House() {
        if (!vboId || !vaoId) {
            initialize();
        }
    }

    void render() {
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};


#endif //GC_HOUSE_H
