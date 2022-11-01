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
    GLuint vaoId, vboId, colorId, verticesEboId, colorsEboId, vaoId2;

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
        GLuint verticesIndices[] = {
                0, 1, 2,
                0, 2, 3,
        };
        GLfloat colors[] = {
                1.0f, 0.0f, 0.0f, 1.0f, // 0
                0.0f, 1.0f, 0.0f, 1.0f, // 0
                0.0f, 0.0f, 1.0f, 1.0f, // 0
        };
        GLuint colorsIndices[] = {
                0, 0, 0,
                0, 0, 0,
        };


//        glGenVertexArrays(1, &vaoId);
//        glBindVertexArray(vaoId);

        glGenBuffers(1, &vboId);
        glGenBuffers(1, &verticesEboId);
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verticesEboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticesIndices), verticesIndices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

        glGenBuffers(1, &colorId);
        glGenBuffers(1, &colorsEboId);
        glBindBuffer(GL_ARRAY_BUFFER, colorId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, colorsEboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(colorsIndices), colorsIndices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr); // TODO

//        glBindVertexArray(0);
    }

public:
    House() {
        initialize();
    }

    void render() {
//        glBindVertexArray(vaoId);

        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verticesEboId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ARRAY_BUFFER, colorId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, colorsEboId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//        glBindVertexArray(0);
    }
};


#endif //GC_HOUSE_H
