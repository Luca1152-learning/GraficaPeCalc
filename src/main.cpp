#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "utils/render/ShadersUtils.h"
#include "drawable/House.h"
#include "drawable/Tree.h"
#include "drawable/Hills.h"
#include "drawable/Sea.h"
#include "drawable/sun/Sun.h"
#include "utils/color/Colors.h"

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
    // Hills
    drawables.push_back(new Hills());

    // House
    drawables.push_back(new House(
            60.0f, 285.0f, 0.5f, false,
            Color::fromHex("#DEDCDA"), Color::fromHex("#E9E7E8"), Color::fromHex("#7C292E"),
            Color::fromHex("#BA4C40"), Color::fromHex("#458592"), Color::fromHex("#C5A671"),
            Color::fromHex("#966D44"), Color::fromHex("#EFCF9D")
    ));
    drawables.push_back(new House(
            415.0f, 295.0f, 0.37f, true,
            Color::fromHex("#DAC09B"), Color::fromHex("#D3B589"), Color::fromHex("#41494E"), Color::fromHex("#59616C"),
            Color::fromHex("#3C8898"), Color::fromHex("#FBE6BE"), Color::fromHex("#B89A6B"), Color::fromHex("#B89A6B")
    ));
    drawables.push_back(new House(
            750.0f, 260.0f, 0.6f, true,
            Color::fromHex("#D7C6A9"), Color::fromHex("#E7D9C1"), Color::fromHex("#41494E"), Color::fromHex("#59616C"),
            Color::fromHex("#409296"), Color::fromHex("#F8F8EC"), Color::fromHex("#BBA497"), Color::fromHex("#BBA497")
    ));
    drawables.push_back(new House(
            1050.0f, 290.0f, 0.27f, false,
            Color::fromHex("#D7C6A9"), Color::fromHex("#E7D9C1"), Color::fromHex("#9E634B"), Color::fromHex("#B57765"),
            Color::fromHex("#409296"), Color::fromHex("#F8F8EC"), Color::fromHex("#BBA497"), Color::fromHex("#BBA497")
    ));

    // Sun
    Sun *sun = new Sun(150.0f, 600.0f, 55.0f, Color::fromHex("#E5D47C"));
    drawables.push_back(sun);

    // Trees
    drawables.push_back(new Tree({200.0f, 310.0f}, 0.18f));
    drawables.push_back(new Tree({240.0f, 240.0f}, 0.25f));
    drawables.push_back(new Tree({40.0f, 230.0f}, 0.32f));
    drawables.push_back(new Tree({340.0f, 285.0f}, 0.16f));
    drawables.push_back(new Tree({590.0f, 330.0f}, 0.14f));
    drawables.push_back(new Tree({615.0f, 345.0f}, 0.13f));
    drawables.push_back(new Tree({620.0f, 255.0f}, 0.3f));
    drawables.push_back(new Tree({710.0f, 375.0f}, 0.1f));
    drawables.push_back(new Tree({740.0f, 255.0f}, 0.3f));
    drawables.push_back(new Tree({840.0f, 305.0f}, 0.25f));
    drawables.push_back(new Tree({1200.0f, 260.0f}, 0.20f));
    drawables.push_back(new Tree({1240.0f, 245.0f}, 0.20f));

    // Sea
    drawables.push_back(new Sea());
}

void render() {
    glUseProgram(shaderProgramId);

    for (auto it: drawables) {
        it->render();
    }
    for (auto it: drawables) {
        it->stepAnimation();
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