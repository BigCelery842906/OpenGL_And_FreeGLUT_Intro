#include "Cube.h"
#include <fstream>
#include <iostream>
#include <string>

Vertex* Cube::indexedVertices = nullptr;
Color* Cube::indexedColors = nullptr;
GLushort* Cube::indices = nullptr;

// GLushort Cube::indices[] =
//     {
//     0,1,2, 2,3,0, // front
//     0,3,4, 4,5,0, // right
//     0,5,6, 6,1,0, // top
//     1,6,7, 7,2,1, // left
//     7,4,3, 3,2,7, // bottom
//     4,7,6, 6,5,4 }; // back

int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;

Cube::Cube(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	
	rotationCube = 0.0f;

	
	//DrawCube();
	DrawIndexedCubeAlt();
}

Cube::~Cube()
{
	delete this;
}

void Cube::Draw()
{
	if (indexedVertices != nullptr && indexedColors != nullptr && indices != nullptr)
	{
		DrawIndexedCubeAlt();
	}
	else
	{
		DrawCube();
	}
}

void Cube::Update()
{
	rotationCube += 0.5f;
	if (rotationCube >= 360.0f)
	{
		rotationCube =0.0f;
	}
	if (_position.z < -1)
	{
		_position.z += 0.5;
	}
	else
	{
		_position.z = -100;
	}	
}

void Cube::DrawCube()
{
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(rotationCube, 1.0f, 1.0f, 1.0f);

#pragma region CUBETIME
	glBegin(GL_POLYGON);
	glColor4f(0,0,0,0);
	glVertex3f(-0.5, -0.5, 0.5);
	glColor4f(1,0,0,0);
	glVertex3f(0.5, -0.5, 0.5);
	glColor4f(1,1,0,0);
	glVertex3f(0.5, 0.5, 0.5);
	glColor4f(0,1,0,0);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0,1,0,0);
	glVertex3f(-0.5, 0.5, 0.5);
	glColor4f(1,1,0,0);
	glVertex3f(0.5, 0.5, 0.5);
	glColor4f(0,1,1,0);
	glVertex3f(0.5, 0.5, -0.5);
	glColor4f(0,0,1,0);
	glVertex3f(-0.5, 0.5, -0.5); //minus in here
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0,0,1,0);
	glVertex3f(-0.5, 0.5, -0.5);
	glColor4f(0,1,1,0);
	glVertex3f(0.5, 0.5, -0.5);
	glColor4f(1,0,1,0);
	glVertex3f(0.5, -0.5, -0.5);
	glColor4f(1,1,1,0);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1,1,1,0);
	glVertex3f(-0.5, -0.5, -0.5);
	glColor4f(1,0,1,0);
	glVertex3f(0.5, -0.5, -0.5);
	glColor4f(1,0,0,0);
	glVertex3f(0.5, -0.5, 0.5);
	glColor4f(0,0,0,0);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1,0,0,0);
	glVertex3f(0.5, -0.5, 0.5);
	glColor4f(1,0,1,0);
	glVertex3f(0.5, -0.5, -0.5);
	glColor4f(0,1,1,0);
	glVertex3f(0.5, 0.5, -0.5);
	glColor4f(1,1,0,0);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1,1,1,0);
	glVertex3f(-0.5, -0.5,-0.5);
	glColor4f(0,0,0,0);
	glVertex3f(-0.5, -0.5, 0.5);
	glColor4f(0,1,0,0);
	glVertex3f(-0.5, 0.5, 0.5);
	glColor4f(0,0,1,0);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

#pragma endregion
	
	glCullFace(GL_BACK);
	
	glPopMatrix();
}

void Cube::DrawIndexedCubeAlt()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	glColorPointer(3, GL_FLOAT, 0, indexedColors);

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(rotationCube, 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, indices);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

bool Cube::Load(const char* path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Cant Open Text File " << path << std::endl;
		return false;
	}

	inFile >> numVertices;
	std::cout << "numVertices = " << numVertices << std::endl;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
	//Use file to populate indexed vertices
		inFile >> indexedVertices[i].x >> indexedVertices[i].y >> indexedVertices[i].z;
		std::cout << indexedVertices[i].x << " " << indexedVertices[i].y << " " << indexedVertices[i].z << std::endl;
		
	}
	//Load Color Info
	inFile >> numColors;
	std::cout << "numColors = " << numColors << std::endl;
	indexedColors = new Color[numColors];
	for (int i = 0; i < numColors; i++)
	{
		inFile >> indexedColors[i].r >> indexedColors[i].g >> indexedColors[i].b;
		std::cout << indexedColors[i].r << " " << indexedColors[i].g << " " << indexedColors[i].b << std::endl;
		
	}
	
	//Load Indice Info
	
	inFile >> numIndices;
	std::cout << "numIndices = " << numIndices << std::endl;

	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		std::cout << "Indices Array Triggered";
		inFile >> indices[i];
		std::cout << indices[i] << std::endl;
		
	}

	inFile.close();
	return true;
}
