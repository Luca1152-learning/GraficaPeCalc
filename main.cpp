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
#include "SOIL.h"

using namespace std;

//////////////////////////////////////

GLuint
VaoId,
VboId,
EboId,
ColorBufferId,
ProgramId,
myMatrixLocation,
codColLocation;
int codCol;

float width = 80.f, height = 60.f;
glm::mat4
myMatrix, resizeMatrix = glm::ortho(-width, width, -height, height), scaleMatrix, translationMatrix;

GLuint texture;

void CreateVBO(void)
{
	// coordonatele varfurilor
	static const GLfloat Vertices[] =
	{
	// coordonate,                culori,                      coordonate de texturare,
	-5.0f, -5.0f, 0.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,      0.0f, 0.0f, // stanga jos
	 5.0f,  -5.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f, 1.0f,      1.0f, 0.0f,  // dreapta jos
	 5.0f,  5.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f, 1.0f,      1.0f, 1.0f, // dreapta sus
	-5.0f,  5.0f, 0.0f, 1.0f,     1.0f, 0.0f, 1.0f, 1.0f,      0.0f, 1.0f  // stanga sus
	};

	// indici pentru trasarea unor primitive
	static const GLuint Indices[] =
	{
	  0, 1, 2, // Primul triunghi
	  3, 0, 2, //  Al doilea triunghi
	};

	// se creeaza un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
	glGenVertexArrays(1, &VaoId);
	// se creeaza un buffer nou (atribute)
	glGenBuffers(1, &VboId);
	// se creeaza un buffer nou (indici)
	glGenBuffers(1, &EboId);

	// legarea VAO 
	glBindVertexArray(VaoId);

	// legarea buffer-ului "Array"
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// punctele sunt "copiate" in bufferul curent
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// legarea buffer-ului "Element" (indicii)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	// indicii sunt "copiati" in bufferul curent
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	// se activeaza lucrul cu atribute; atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);

	// se activeaza lucrul cu atribute; atributul 1 = culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));

	// se activeaza lucrul cu atribute; atributul 2 = coordonate de texturare
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));

}

void DestroyVBO(void)
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glDeleteBuffers(1, &EboId);
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
	// Pentru shaderul de fragmente
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);
	codColLocation = glGetUniformLocation(ProgramId, "codCuloare");
}

void LoadTexture(void)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image("text_smiley_face.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 0.5f, 1.0f));
	translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(30.0f, 30.0f, 1.0f));
	
	// 0 - default
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));

	// 1 - colorat - scalare + translatie
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	myMatrix = resizeMatrix * translationMatrix * scaleMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));

	// 2 - texturat - translatie + scalare
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	// Functii pentru texturi
	LoadTexture();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// transmitere variabile uniforme pentru shaderul de fragmente
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);
	myMatrix = resizeMatrix * scaleMatrix * translationMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));


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