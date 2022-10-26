/* DESCRIERE: DREPTUNGHI CU SATELIT -- varianta cu OpenGL "nou"
	- utilizeaza diverse transformari si compunerea acestora folosind biblioteca glm
	- functii pentru utilizarea mouse-ului
*/

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"

// Din biblioteca glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

GLuint
        VaoId,
        VboId,
        ColorBufferId,
        ProgramId,
        myMatrixLocation,
        matrScaleLocation,
        matrTranslLocation,
        matrRotlLocation,
        codColLocation;

int codCol;
float PI = 3.141592, angle = 0;
float tx = 0;
float ty = 0;
float i = 0.0, alpha = 0.0, step = 0.3, beta = 0.002;
glm::mat4
        myMatrix, resizeMatrix, matrTransl1, matrTransl2, matrTransl3, matrScale1, matrScale2, matrRot, matrDepl;
glm::vec3 center;

void displayMatrix() {
    for (int ii = 0; ii < 4; ii++) {
        for (int jj = 0; jj < 4; jj++)
            cout << myMatrix[ii][jj] << "  ";
        cout << endl;
    };
    cout << "\n";
};

void miscad(void) {
    i = i + alpha;
    if (i > 350.0)
        alpha = -step;
    else if (i < -350.0)
        alpha = step;
    angle = angle - beta;
    glutPostRedisplay();
}

void miscas(void) {
    i = i + alpha;
    if (i < -350.0)
        alpha = step;
    else if (i > 350.0)
        alpha = -step;
    angle = angle + beta;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                alpha = -step;
            glutIdleFunc(miscas);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                alpha = step;
            glutIdleFunc(miscad);
            break;
        default:
            break;
    }
}

void CreateVBO(void) {
    // varfurile
    GLfloat Vertices[] = {
            // Fundal
            // Triunghiul 1
            0.0f, 0.0f, 0.0f, 1.0f,
            400.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 400.0f, 0.0f, 1.0f,
            // Triunghiul 2
            400.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 400.0f, 0.0f, 1.0f,
            400.0f, 400.0f, 0.0f, 1.0f,

            // Varfuri pentru poligonul convex
            // Triunghiul 1
            50.0f, 150.0f, 0.0f, 1.0f,
            100.0f, 150.0f, 0.0f, 1.0f,
            100.0f, 200.0f, 0.0f, 1.0f,
            // Triunghiul 2
            50.0f, 150.0f, 0.0f, 1.0f,
            100.0f, 200.0f, 0.0f, 1.0f,
            50.0f, 250.0f, 0.0f, 1.0f,

            // Varfuri pentru poligonul concav
            // Triunghiul 1
            150.0f, 150.0f, 0.0f, 1.0f,
            250.0f, 150.0f, 0.0f, 1.0f,
            150.0f, 250.0f, 0.0f, 1.0f,
            250.0f, 150.0f, 0.0f, 1.0f,
            250.0f, 250.0f, 0.0f, 1.0f,
            200.0f, 200.0f, 0.0f, 1.0f,
    };

    // culorile varfurilor din colturi
    GLfloat Colors[] = {
            // Fundal gradient
            1.0f, 1.0f, 1.0f, 1.0f,
            0.81f, 0.82f, 0.85f, 1.0f,
            0.81f, 0.82f, 0.85f, 1.0f,
            0.81f, 0.82f, 0.85f, 1.0f,
            0.81f, 0.82f, 0.85f, 1.0f,
            0.32f, 0.59f, 0.8f, 1.0f,

            // Poligon convex
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,

            // Poligon concav
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
    };

    // se creeaza un buffer nou
    glGenBuffers(1, &VboId);
    // este setat ca buffer curent
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    // punctele sunt "copiate" in bufferul curent
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);
    // se activeaza lucrul cu atribute; atributul 0 = pozitie
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // un nou buffer, pentru culoare
    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    // atributul 1 =  culoare
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void DestroyVBO(void) {
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VboId);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
}

void CreateShaders(void) {
    ProgramId = LoadShaders("03_02_Shader.vert", "03_02_Shader.frag");
    glUseProgram(ProgramId);
}

void DestroyShaders(void) {
    glDeleteProgram(ProgramId);
}

void Initialize(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
    CreateVBO();
    CreateShaders();
    codColLocation = glGetUniformLocation(ProgramId, "codCuloare");
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
}

void RenderFunction(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    resizeMatrix = glm::ortho(0.0f, 400.0f, 0.0f,400.0f); // scalam, "aducem" scena la "patratul standard" [-1,1]x[-1,1]

    // Fara transformari
    myMatrix = resizeMatrix;
    codCol = 0;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glUniform1i(codColLocation, codCol);
    glDrawArrays(GL_TRIANGLES, 0, 18);

    // Cu transformari
    center = glm::vec3(150.0, 200.0, 0.0); // Centrul pentru cele doua poligoane
    matrTransl1 = glm::translate(glm::mat4(1.0f), -center); // Translatie catre origine a punctului
    matrRot = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotatie in jurul originii, de 180 de grade
    matrTransl2 = glm::translate(glm::mat4(1.0f), center); // Translate inapoi catre centru
    matrTransl3 = glm::translate(glm::mat4(1.0f), glm::vec3(000.0f, -125.0f, 0.0f)); // Translate cu 125 mai jos
    myMatrix = resizeMatrix * matrTransl3 * matrTransl2 * matrRot * matrTransl1;

    codCol = 0;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glUniform1i(codColLocation, codCol);
    glDrawArrays(GL_TRIANGLES, 6, 18);

    glutSwapBuffers();
    glFlush();
}

void Cleanup(void) {
    DestroyShaders();
    DestroyVBO();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Dreptunghi cu satelit - OpenGL <<nou>>");
    glewInit();
    Initialize();
    glutDisplayFunc(RenderFunction);
    glutMouseFunc(mouse);
    glutCloseFunc(Cleanup);
    glutMainLoop();
}