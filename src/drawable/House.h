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

class House : public Drawable {
private:
    void initialize() final {
        float vertices[] = {
                100.0f, 100.0f, // bottom left
                200.0f, 100.0f, // bottom right
                200.0f, 200.0f, // top right
                100.0f, 100.0f, // bottom left
                200.0f, 200.0f, // top right
                100.0f, 200.0f // top left
        };
        GLfloat colors[] = {
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
        };

        // Bind VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Vertices VBO
        glGenBuffers(1, &verticesVbo);
        glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // Colors VBO
        glGenBuffers(1, &colorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
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
