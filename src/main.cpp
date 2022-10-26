#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

// New OpenGL
GLuint VboId1,
        ColorBufferId1,
        VertexShaderId,
        FragmentShaderId,
        ProgramId;

const GLchar *VertexShader = {
        "#version 400\n"\
        "layout(location=0) in vec4 in_Position;\n"\
        "layout(location=1) in vec4 in_Color;\n"\
        "out vec4 ex_Color;\n"\
        "void main(void)\n"\
        "{\n"\
        "  gl_Position = in_Position;\n"\
        "  ex_Color = in_Color;\n"\
        "}\n"
};

const GLchar *FragmentShader = {
        "#version 400\n"\

        "in vec4 ex_Color;\n"\
        "out vec4 out_Color;\n"\

        "void main(void)\n"\
        "{\n"\
        "  out_Color = ex_Color;\n"\
        "}\n"
};

void initialize() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void drawBlueRectangle() {
    GLfloat vertices[] = {
            // Blue rectangle
            -0.95f, -0.675f, 0.0f, 1.0f,
            -0.65f, -0.675f, 0.0f, 1.0f,
            -0.95f, 0.03f, 0.0f, 1.0f,
            -0.65f, -0.675f, 0.0f, 1.0f,
            -0.65f, 0.03f, 0.0f, 1.0f,
            -0.95f, 0.03f, 0.0f, 1.0f,
            // Red polygon 1
            -1.0f, -1.0f, 0.0f, 1.0f,
            -0.75f, -0.966f, 0.0f, 1.0f,
            -0.612f, -0.03f, 0.0f, 1.0f,
            -0.75f, -0.966f, 0.0f, 1.0f,
            -0.612f, -0.03f, 0.0f, 1.0f,
            -0.5f, -0.6f, 0.0f, 1.0f,
            // Red polygon 2
            -0.375f, 0.0f, 0.0f, 1.0f,
            -0.875f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.16f, 0.0f, 1.0f,
            -0.5f, 0.16f, 0.0f, 1.0f,
            -0.375f, 0.666f, 0.0f, 1.0f,
            -0.125f, -0.333f, 0.0f, 1.0f,
            // Yellow polygon
            0.625f, 0.0f, 0.0f, 1.0f,
            0.125f, 0.0f, 0.0f, 1.0f,
            0.625f, 0.666f, 0.0f, 1.0f,
            0.5f, 0.166f, 0.0f, 1.0f,
            0.625f, 0.666f, 0.0f, 1.0f,
            0.875f, -0.333f, 0.0f, 1.0f,

    };
    GLfloat color[] = {
            // Blue rectangle
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            // Red polygon 1
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            // Red polygon 2
            1.0f, 0.0f, 0.25f, 1.0f,
            1.0f, 0.0f, 0.25f, 1.0f,
            1.0f, 0.0f, 0.25f, 1.0f,
            1.0f, 0.0f, 0.25f, 1.0f,
            1.0f, 0.0f, 0.25f, 1.0f,
            1.0f, 0.0f, 0.25f, 1.0f,
            // Yellow polygon
            1.0f, 0.75f, 0.25f, 1.0f,
            1.0f, 0.75f, 0.25f, 1.0f,
            1.0f, 0.75f, 0.25f, 1.0f,
            1.0f, 0.75f, 0.25f, 1.0f,
            1.0f, 0.75f, 0.25f, 1.0f,
            1.0f, 0.75f, 0.25f, 1.0f,
    };

    glGenBuffers(1, &VboId1);
    glBindBuffer(GL_ARRAY_BUFFER, VboId1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &ColorBufferId1);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void createVBO() {
    drawBlueRectangle();
}

void createShaders() {
    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, nullptr);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, nullptr);
    glCompileShader(FragmentShaderId);

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);
}

void destroyVBO() {

}

void destroyShaders() {
    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);
}

void cleanUp() {
    destroyShaders();
    destroyVBO();
}

void renderFunction() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    createVBO();
    createShaders();
    glDrawArrays(GL_TRIANGLES, 0, 24);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Poligoane");
    glewInit();

    initialize();

    glutDisplayFunc(renderFunction);
    glutCloseFunc(cleanUp);
    glutMainLoop();

    return 0;
}