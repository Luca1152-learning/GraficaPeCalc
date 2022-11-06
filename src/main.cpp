#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "utils/ShadersUtils.h"
#include "drawable/House.h"
#include "utils/Colors.h"

using namespace glm;
using namespace std;

GLuint shaderProgramId;

vector<Drawable *> drawables;

GLFWwindow *initializeWindow() {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(Constants::WIDTH, Constants::HEIGHT, "macOS OpenGL", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glewInit();
    glfwSwapInterval(1);

    return window;
}

void initializeShaders() {
    shaderProgramId = ShadersUtils::loadShaders("shaders/shader.vert", "shaders/shader.frag");
    Constants::MATRIX_LOCATION = glGetUniformLocation(shaderProgramId, "matrix");
}

void initializeScene() {
    House *houseA = new House(150.0f, 150.0f, 1.0f, false);
    drawables.push_back(houseA);

    House *houseB = new House(350.0f, 350.0f, 0.8f, true);
    drawables.push_back(houseB);
}

void render() {
    glUseProgram(shaderProgramId);

    for (auto it: drawables) {
        it->render();
    }
}

void cleanUp() {
    glDeleteProgram(shaderProgramId);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

int main() {
    GLFWwindow *window = initializeWindow();
    initializeShaders();
    initializeScene();

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClearColor(Colors::SKY.getR(), Colors::SKY.getG(), Colors::SKY.getB(), Colors::SKY.getA());
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanUp();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}