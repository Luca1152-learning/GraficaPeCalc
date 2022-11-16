/* INDEXARE
Elemente de noutate:
   - folosirea indexarii varfurilor: elemente asociate (matrice, buffer)
   - desenarea se face folosind functia glDrawElements()
   */
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "loadShaders.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

using namespace std;

//////////////////////////////////////

GLuint
VaoId,
VboId,
EboId,
ColorBufferId,
ProgramId,
myMatrixLocation;

float width = 80.f, height = 60.f;
glm::mat4
myMatrix, resizeMatrix = glm::ortho(-width, width, -height, height);


vector<GLfloat> varfuri, culori;
vector<GLuint> indici;

const int n = 10;
const GLfloat radiuses[] = { 10.0f, 20.0f };

void CreateVBO(void)
{
	for (int i = 0; i < 2; i++) {
		GLfloat radius = radiuses[i];
		for (int k = 0; k < n; k++) {
			GLfloat x, y;

			GLfloat angleRad = 2 * k * glm::pi<GLfloat>() / n;
			x = radius * glm::cos(angleRad);
			y = radius * glm::sin(angleRad);

			// Varfuri
			varfuri.push_back(x);
			varfuri.push_back(y);
			varfuri.push_back(0.0f);
			varfuri.push_back(1.0f);

			// Culoare
			culori.push_back(0.0f);
			culori.push_back(0.0f);
			culori.push_back(0.0f);
			culori.push_back(1.0f);
		}
	}

	// Indici - cerc mic
	for (int i = 0; i < n - 1; i++) {
		indici.push_back(i);
		indici.push_back(i + 1);
	}
	indici.push_back(n - 1);
	indici.push_back(0);


	// Indici - cerc mare
	for (int i = n; i < 2 * n - 1; i++) {
		indici.push_back(i);
		indici.push_back(i + 1);
	}
	indici.push_back(2 * n - 1);
	indici.push_back(n);

	// Indici - legaturi cerc mic->cerc mare
	for (int i = 0; i < n; i++) {
		indici.push_back(i);
		indici.push_back(n + i);
	}
	for (int i = 1; i < n; i++) {
		indici.push_back(i);
		indici.push_back(n + i - 1);
	}
	indici.push_back(0);
	indici.push_back(2 * n - 1);

	GLfloat* vf_pos = varfuri.data();
	GLfloat* vf_col = culori.data();
	GLuint* vf_ind = indici.data();

	// se creeaza un buffer nou pentru varfuri
	glGenBuffers(1, &VboId);
	// buffer pentru indici
	glGenBuffers(1, &EboId);
	// se creeaza / se leaga un VAO (Vertex Array Object)
	glGenVertexArrays(1, &VaoId);

	// legare VAO
	glBindVertexArray(VaoId);

	// buffer-ul este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);

	// buffer-ul va contine atat coordonatele varfurilor, cat si datele de culoare
	glBufferData(GL_ARRAY_BUFFER, (varfuri.size() + culori.size()) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, varfuri.size() * sizeof(GLfloat), vf_pos);
	glBufferSubData(GL_ARRAY_BUFFER, varfuri.size() * sizeof(GLfloat), culori.size() * sizeof(GLfloat), vf_col);

	// buffer-ul pentru indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indici.size() * sizeof(GLuint), vf_ind, GL_STATIC_DRAW);

	// se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(varfuri.size() * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &EboId);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

void CreateShaders(void)
{
	ProgramId = LoadShaders("06_02_Shader.vert", "06_02_Shader.frag");
	glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	CreateVBO();
	CreateShaders();
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
}
void RenderFunction(void)
{
	glLineWidth(1.5f);
	glClear(GL_COLOR_BUFFER_BIT);
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_LINES, indici.size(), GL_UNSIGNED_INT, (void*)(0));
	// De realizat desenul folosind segmente de dreapta
	glFlush();
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Utilizarea indexarii varfurilor");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}