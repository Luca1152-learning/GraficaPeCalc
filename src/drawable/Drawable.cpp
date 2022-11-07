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

Drawable::Drawable(float translateX, float translateY, float scaleX, float scaleY, bool flip) :
        translate({translateX, translateY}), scale({scaleX, scaleY}), flip(flip) {
}

void Drawable::render() {
    mat4 translateTo00Matrix = glm::translate(mat4(1.0f), -(vec3) triangleVertices.getCenter());
    mat4 rotationAround00Matrix = glm::rotate(mat4(1.0f), radians(rotationAround00Deg), vec3(0.0f, 0.0f, 1.0f));
    mat4 translateToCenterOfRotationMatrix = glm::translate(mat4(1.0f), -vec3(centerOfRotation, 0.0f));
    mat4 rotationAroundCenterOfRotationMatrix = glm::rotate(
            mat4(1.0f), radians(rotationAroundCenterDeg), vec3(0.0f, 0.0f, 1.0f)
    );
    mat4 translateFromCenterOfRotationTo00Matrix = glm::translate(
            mat4(1.0f), vec3(centerOfRotation, 0.0f)
    );
    mat4 flipMatrix = flip ? glm::rotate(mat4(1.0f), radians(180.0f), vec3(0.0f, 1.0f, 0.0f)) : mat4(1.0f);
    mat4 scaleMatrix = glm::scale(mat4(1.0f), vec3(scale, 0.0f));
    mat4 translateToXYMatrix = glm::translate(mat4(1.0f), vec3(translate, 0.0f));
    mat4 resizeMatrix = Constants::RESIZE_MATRIX;

    mat4 resultingMatrix =
            resizeMatrix * translateToXYMatrix * scaleMatrix * flipMatrix * translateFromCenterOfRotationTo00Matrix *
            rotationAroundCenterOfRotationMatrix * translateToCenterOfRotationMatrix * rotationAround00Matrix;

    glUniformMatrix4fv(Constants::MATRIX_LOCATION, 1, GL_FALSE, &resultingMatrix[0][0]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, triangleVertices.getSize());
    glBindVertexArray(0);
}

void Drawable::stepAnimation() {}

void Drawable::setCenterOfRotation(float centerX, float centerY) {
    centerOfRotation = {centerX, centerY};
}
