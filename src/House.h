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
    GLuint vaoId, vboId, eboId;

    Color wallColor = Color(255, 0, 255);
    Color roofColor = Color(255, 0, 0);
    Color doorColor = Color(255, 0, 255);

    void initialize() {
        float vertices[] = {
                -0.5f, -0.5f, // 0 bottom left
                0.5f, -0.5f, // 1 bottom right
                0.5f, 0.5f, // 2 top right
                -0.5f, 0.5f // 3 top left
        };
        GLuint indices[] = {
                0, 1, 2,
                0, 2, 3,
        };

        glGenVertexArrays(1, &vaoId);
        glGenBuffers(1, &vboId);
        glGenBuffers(1, &eboId);

        glBindVertexArray(vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

public:
    House() {
        initialize();
    }

    void render() {
        glBindVertexArray(vaoId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};


#endif //GC_HOUSE_H
