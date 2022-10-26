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
float width = 450, height = 300;
float i = 0.0, alpha = 0.0, step = 0.15, beta = 0.002;
glm::mat4
        myMatrix, resizeMatrix, matrTransl, matrRot;

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
            // Axa orizontala
            -450.0f, 0.0f, 0.0f, 1.0f,
            450.0f, 0.0f, 0.0f, 1.0f,

            // Patrat
            -25.0f, -25.0f, 0.0f, 1.0f,
            25.0f, -25.0f, 0.0f, 1.0f,
            25.0f, 25.0f, 0.0f, 1.0f,
            -25.0f, 25.0f, 0.0f, 1.0f,
    };

    // culorile varfurilor din colturi
    GLfloat Colors[] = {
            // Axa orizontala
            0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f,

            // Patrat
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
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

    resizeMatrix = glm::ortho(-400.0f, 400.0f, -80.0f, 400.0f);

    // Axa orizontala
    myMatrix = resizeMatrix;

    codCol = 0;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glUniform1i(codColLocation, codCol);
    glDrawArrays(GL_LINES, 0, 2);

    // Patratul
    // Roteste patratul cu i grade (are deja centrul in (0,0))
    matrRot = glm::rotate(glm::mat4(1.0f), glm::radians(i), glm::vec3(0.0, 0.0, 1.0));
    // Dupa ce ai rotit patratul, muta-l, folosind i
    matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0, 0.0)); // controleaza translatia de-a lungul lui Ox
    myMatrix = resizeMatrix * matrTransl * matrRot;

    codCol = 0;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glUniform1i(codColLocation, codCol);
    glDrawArrays(GL_POLYGON, 2, 4);

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