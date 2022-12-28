// Survolarea unei sfere.
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
using namespace std;

// identificatori 
GLuint
	VboId,
	EboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	matrUmbraLocation,
	viewLocation,
	projLocation,
	matrRotlLocation,
	lightColorLocation,
	lightPosLocation,
	viewPosLocation,
	codColLocation;
int codCol;

float const PI = 3.141592f;
// Elemente pentru reprezentarea suprafetei
// (1) intervalele pentru parametrii considerati (u si v)
float const U_MIN = -PI / 2, U_MAX = PI / 2, V_MIN = 0, V_MAX = 2 * PI ;
// (2) numarul de paralele/meridiane, de fapt numarul de valori ptr parametri
int const NR_PARR = 7, NR_MERID = 25;
// (3) pasul cu care vom incrementa u, respectiv v
float step_u = (U_MAX - U_MIN) / NR_PARR, step_v = (V_MAX - V_MIN) / NR_MERID;

// alte variabile
float radius = 50;
int index, index_aux;

// variabile pentru matricea de vizualizare
float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;
float alpha = 0.0f, beta = 0.0f, dist = 300.0f;
float Obsx, Obsy, Obsz;
float Vx = 0.0f, Vy = 0.0f, Vz = -1.0f;
float incr_alpha1 = 0.01f, incr_alpha2 = 0.01f;

// variabile pentru matricea de proiectie
float width = 800, height = 600, znear = 1, fov = 30;

// pentru fereastra de vizualizare 
GLint winWidth = 1000, winHeight = 600;

// vectori
glm::vec3 Obs, PctRef, Vert;

// matrice utilizate
glm::mat4 view, projection;

// Lighting
GLint lightColorLoc, lightPosLoc, viewPosLoc;

// Umbra
// matrice utilizate
glm::mat4 myMatrix, matrRot;
// sursa de lumina
float xL = 500.f, yL = 100.f, zL = 400.f;
// matricea umbrei
float matrUmbra[4][4];

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case '-':
		dist -= 5.0;
		break;
	case '+':
		dist += 5.0;
		break;
	}
	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		beta -= 0.01f;
		break;
	case GLUT_KEY_RIGHT:
		beta += 0.01f;
		break;
	case GLUT_KEY_UP:
		alpha += incr_alpha1;
		if (abs(alpha - PI / 2) < 0.05)
		{
			incr_alpha1 = 0.f;
		}
		else
		{
			incr_alpha1 = 0.01f;
		}
		break;
	case GLUT_KEY_DOWN:
		alpha -= incr_alpha2;
		if (abs(alpha + PI / 2) < 0.05)
		{
			incr_alpha2 = 0.f;
		}
		else
		{
			incr_alpha2 = 0.01f;
		}
		break;
	}
}
void CreateVBO(void)
{
	// varfurile 
	// (4) Matricele pentru varfuri, culori, indici
	glm::vec4 Vertices[(NR_PARR + 1) * NR_MERID + 6];
	glm::vec3 Colors[(NR_PARR + 1) * NR_MERID + 6];
	glm::vec3 Normals[(NR_PARR + 1) * NR_MERID + 6];
	GLushort Indices[2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID + 2 * 2 * NR_MERID + 2 * 3 * NR_MERID + 6];
	for (int merid = 0; merid < NR_MERID; merid++)
	{
		for (int parr = 0; parr < NR_PARR + 1; parr++)
		{
			// implementarea reprezentarii parametrice 
			float u = U_MIN + parr * step_u; // valori pentru u si v
			float v = V_MIN + merid * step_v;
			float x_vf = radius * cosf(v);
			float y_vf = radius * sinf(v);
			float z_vf = u * 40;

			// identificator ptr varf; coordonate + culoare + indice la parcurgerea meridianelor
			index = merid * (NR_PARR + 1) + parr;
			Vertices[index] = glm::vec4(x_vf, y_vf, z_vf, 1.0);
			Colors[index] = glm::vec3(0.1f + sinf(u), 0.1f + cosf(v), 0.1f + -1.5 * sinf(u));
			Normals[index] = glm::vec3(x_vf, y_vf, z_vf);
			Indices[index] = index;

			// indice ptr acelasi varf la parcurgerea paralelelor
			index_aux = parr * (NR_MERID)+merid;
			Indices[(NR_PARR + 1) * NR_MERID + index_aux] = index;

			// indicii pentru desenarea fetelor, pentru varful curent sunt definite 4 varfuri
			if ((parr + 1) % (NR_PARR + 1) != 0) // varful considerat sa nu fie Polul Nord
			{
				int AUX = 2 * (NR_PARR + 1) * NR_MERID;
				int index1 = index; // varful v considerat
				int index2 = index + (NR_PARR + 1); // dreapta lui v, pe meridianul urmator
				int index3 = index2 + 1;  // dreapta sus fata de v
				int index4 = index + 1;  // deasupra lui v, pe acelasi meridian
				if (merid == NR_MERID - 1)  // la ultimul meridian, trebuie revenit la meridianul initial
				{
					index2 = index2 % (NR_PARR + 1);
					index3 = index3 % (NR_PARR + 1);
				}
				Indices[AUX + 4 * index] = index1;  // unele valori ale lui Indices, corespunzatoare Polului Nord, au valori neadecvate
				Indices[AUX + 4 * index + 1] = index2;
				Indices[AUX + 4 * index + 2] = index3;
				Indices[AUX + 4 * index + 3] = index4;
			}
		}
	};
	
	// Center - top
	int centerTopIndex = (NR_PARR + 1) * NR_MERID;
	float usedMaxU = U_MIN + NR_PARR * step_u;
	Vertices[centerTopIndex] = glm::vec4(0.0f, 0.0f, usedMaxU * 40, 1.0);
	Normals[centerTopIndex] = glm::vec3(0.0f, 0.0f, usedMaxU * 40);
	Colors[centerTopIndex] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Lines - Indices top
	for (int i = 0; i < NR_MERID; i++)
	{
		int startIndicesTop = 2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID;

		Indices[startIndicesTop + 2 * i] = centerTopIndex;

		int currentMeridianIndex = i * (NR_PARR + 1) + NR_PARR;
		Indices[startIndicesTop + 2 * i + 1] = currentMeridianIndex;
	};
	// Triangles - Indices top
	for (int i = 0; i < NR_MERID; i++)
	{
		int startIndicesTop = 2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID + 2 * 2 * NR_MERID;

		Indices[startIndicesTop + 3 * i] = centerTopIndex;

		int currentMeridianIndex = i * (NR_PARR + 1) + NR_PARR;
		Indices[startIndicesTop + 3 * i + 1] = currentMeridianIndex;

		int nextMeridianIndex = (i + 1) % NR_MERID * (NR_PARR + 1) + NR_PARR;
		Indices[startIndicesTop + 3 * i + 2] = nextMeridianIndex;
	};

	// Center - bottom
	int centerBottomIndex = centerTopIndex + 1;
	float usedMinU = U_MIN + 0 * step_u;
	Vertices[centerBottomIndex] = glm::vec4(0.0f, 0.0f, usedMinU * 40, 1.0);
	Normals[centerBottomIndex] = glm::vec3(0.0f, 0.0f, usedMinU * 40);
	Colors[centerBottomIndex] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Lines - Indices bottom
	for (int i = 0; i < NR_MERID; i++)
	{
		int startIndicesBottom = 2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID + 2 * NR_MERID;

		Indices[startIndicesBottom + 2 * i] = centerBottomIndex;

		int currentMeridianIndex = i * (NR_PARR + 1) + 0;
		Indices[startIndicesBottom + 2 * i + 1] = currentMeridianIndex;
	};
	// Triangles - Indices bottom
	for (int i = 0; i < NR_MERID; i++)
	{
		int startIndicesBottom = 2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID + 2 * 2 * NR_MERID + 3 * NR_MERID;

		Indices[startIndicesBottom + 3 * i] = centerBottomIndex;

		int currentMeridianIndex = i * (NR_PARR + 1) + 0;
		Indices[startIndicesBottom + 3 * i + 1] = currentMeridianIndex;

		int nextMeridianIndex = (i + 1) % NR_MERID * (NR_PARR + 1) + 0;
		Indices[startIndicesBottom + 3 * i + 2] = nextMeridianIndex;
	};

	// "Ground"
	int firstGroundIndex = (NR_PARR + 1) * NR_MERID + 2;
	// Varfuri
	Vertices[firstGroundIndex] = glm::vec4(-1500.0f, -1500.0f, -300.0f, 1.0f);
	Vertices[firstGroundIndex+1] = glm::vec4(1500.0f, -1500.0f, -300.0f, 1.0f);
	Vertices[firstGroundIndex+2] = glm::vec4(1500.0f, 1500.0f, -300.0f, 1.0f);
	Vertices[firstGroundIndex+3] = glm::vec4(-1500.0f, 1500.0f, -300.0f, 1.0f);
	// Normale
	Normals[firstGroundIndex] = glm::vec3(0.0f, 0.0f, 1.0f);
	Normals[firstGroundIndex+1] = glm::vec3(0.0f, 0.0f, 1.0f);
	Normals[firstGroundIndex+2] = glm::vec3(0.0f, 0.0f, 1.0f);
	Normals[firstGroundIndex+3] = glm::vec3(0.0f, 0.0f, 1.0f);
	// Culori
	Colors[firstGroundIndex] = glm::vec4(1.0f, 1.0f, 0.9f, 1.0f);
	Colors[firstGroundIndex+1] = glm::vec4(1.0f, 1.0f, 0.9f, 1.0f);
	Colors[firstGroundIndex+2] = glm::vec4(1.0f, 1.0f, 0.9f, 1.0f);
	Colors[firstGroundIndex+3] = glm::vec4(1.0f, 1.0f, 0.9f, 1.0f);
	// Indici
	int firstGroundEboIndex = 2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID + 2 * 2 * NR_MERID + 2 * 3 * NR_MERID;
	Indices[firstGroundEboIndex] = firstGroundIndex + 1;
	Indices[firstGroundEboIndex+1] = firstGroundIndex + 2;
	Indices[firstGroundEboIndex+2] = firstGroundIndex;
	Indices[firstGroundEboIndex+3] = firstGroundIndex + 2;
	Indices[firstGroundEboIndex+4] = firstGroundIndex;
	Indices[firstGroundEboIndex+5] = firstGroundIndex + 3;

	// generare VAO/buffere
	glGenBuffers(1, &VboId); // atribute
	glGenBuffers(1, &EboId); // indici

	// legare+"incarcare" buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors) + sizeof(Normals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors), sizeof(Normals), Normals);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	// atributele; 
	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1); // atributul 1 = culoare
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)sizeof(Vertices));
	glEnableVertexAttribArray(2); // atributul 2 = normala
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(sizeof(Vertices) + sizeof(Colors)));
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glDeleteBuffers(1, &EboId);
}
void CreateShaders(void)
{
	ProgramId = LoadShaders("09_03_Shader.vert", "09_03_Shader.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	myMatrix = glm::mat4(1.0f);
	matrRot = glm::rotate(glm::mat4(1.0f), PI / 8, glm::vec3(0.0, 0.0, 1.0));
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	CreateVBO();
	CreateShaders();
	// locatii pentru shader-e
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	matrUmbraLocation = glGetUniformLocation(ProgramId, "matrUmbra");
	viewLocation = glGetUniformLocation(ProgramId, "view");
	projLocation = glGetUniformLocation(ProgramId, "projection");
	lightColorLocation = glGetUniformLocation(ProgramId, "lightColor");
	lightPosLocation = glGetUniformLocation(ProgramId, "lightPos");
	viewPosLocation = glGetUniformLocation(ProgramId, "viewPos");
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	width = winWidth / 10, height = winHeight / 10;
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//pozitia observatorului
	Obsx = Refx + dist * cos(alpha) * cos(beta);
	Obsy = Refy + dist * cos(alpha) * sin(beta);
	Obsz = Refz + dist * sin(alpha);

	// matrice de vizualizare + proiectie
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);   // se schimba pozitia observatorului	
	glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz); // pozitia punctului de referinta
	glm::vec3 Vert = glm::vec3(Vx, Vy, Vz); // verticala din planul de vizualizare 
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), znear);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// matricea pentru umbra
	float D = -0.5f;
	matrUmbra[0][0] = zL + D; matrUmbra[0][1] = 0; matrUmbra[0][2] = 0; matrUmbra[0][3] = 0;
	matrUmbra[1][0] = 0; matrUmbra[1][1] = zL + D; matrUmbra[1][2] = 0; matrUmbra[1][3] = 0;
	matrUmbra[2][0] = -xL; matrUmbra[2][1] = -yL; matrUmbra[2][2] = D; matrUmbra[2][3] = -1;
	matrUmbra[3][0] = -D * xL; matrUmbra[3][1] = -D * yL; matrUmbra[3][2] = -D * zL; matrUmbra[3][3] = zL;
	glUniformMatrix4fv(matrUmbraLocation, 1, GL_FALSE, &matrUmbra[0][0]);

	// Variabile uniforme pentru iluminare
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLocation, xL, yL, zL);
	glUniform3f(viewPosLocation, Obsx, Obsy, Obsz);

	// "Ground"
	int firstGroundEboIndex = 2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID + 2 * 2 * NR_MERID + 2 * 3 * NR_MERID;
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	myMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (GLvoid*)(firstGroundEboIndex * sizeof(GLushort)));

	// Desenare cilindru
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	myMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	// desenarea fetelor
	for (int patr = 0; patr < (NR_PARR + 1) * NR_MERID; patr++)
	{
		if ((patr + 1) % (NR_PARR + 1) != 0) // nu sunt considerate fetele in care in stanga jos este Polul Nord
			glDrawElements(
				GL_QUADS,
				4,
				GL_UNSIGNED_SHORT,
				(GLvoid*)((2 * (NR_PARR + 1) * (NR_MERID)+4 * patr) * sizeof(GLushort)));
	}
	// fiecare meridian separat
	for (int merid = 0; merid < NR_MERID; merid++)
	{
		glDrawElements(
			GL_LINE_STRIP,
			NR_PARR + 1,
			GL_UNSIGNED_SHORT,
			(GLvoid*)((merid * NR_PARR + merid) * sizeof(GLushort)));
	}
	// fiecare cerc paralel separat
	for (int parr = 1; parr < NR_PARR; parr++)
	{
		glDrawElements(
			GL_LINE_LOOP,
			NR_MERID,
			GL_UNSIGNED_SHORT,
			(GLvoid*)(((NR_PARR + 1) * (NR_MERID)+parr * NR_MERID) * sizeof(GLushort)));
	}
	// Triangles - top & bottom
	glDrawElements(
		GL_TRIANGLES,
		2 * 3 * NR_MERID,
		GL_UNSIGNED_SHORT,
		(GLvoid*)((2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID + 2 * 2 * NR_MERID) * sizeof(GLushort))
	);

	// Desenare umbra cilindru

	glutSwapBuffers();
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 900);
	glutCreateWindow("Iluminare - umbre");
	glewInit();
	Initialize();
	glutIdleFunc(RenderFunction);
	glutDisplayFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}