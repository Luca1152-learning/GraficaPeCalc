#include "Drawable.h"

void Drawable::setupVao() {
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

Drawable::Drawable(float centerX, float centerY, float scaleX, float scaleY, bool flip) :
        centerX(centerX), centerY(centerY), scaleX(scaleX), scaleY(scaleY), flip(flip) {
}

void Drawable::render() {
    mat4 resizeMatrix = Constants::RESIZE_MATRIX;
    mat4 translateTo00Matrix = translate(mat4(1.0f), -(vec3) triangleVertices.getCenter());
    mat4 translateToXYMatrix = translate(mat4(1.0f), vec3(centerX, centerY, 0.0f));
    mat4 scaleMatrix = scale(mat4(1.0f), vec3(scaleX, scaleY, 0.0f));
    mat4 flipMatrix = flip ? rotate(mat4(1.0f), radians(180.0f), vec3(0.0f, 1.0f, 0.0f)) : mat4(1.0f);
    mat4 resultingMatrix = resizeMatrix * translateToXYMatrix * scaleMatrix * flipMatrix * translateTo00Matrix;

    glUniformMatrix4fv(Constants::MATRIX_LOCATION, 1, GL_FALSE, &resultingMatrix[0][0]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, triangleVertices.getSize());
    glBindVertexArray(0);
}
