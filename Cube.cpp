#include "Cube.h"


#pragma region CubeArrays

Vertex Cube::indexedVertices[] =
    {
    1,1,1, -1,1,1,    // v0,v1,
    -1,-1,1, 1,-1,1,  // v2,v3
    1,-1,-1, 1,1,-1,  // v4,v5
    -1,1,-1, -1,-1,-1 // v6,v7
    }; 

Color Cube::indexedColors[] =
    {
    1,1,1, 1,1,0, // v0,v1,
    1,0,0, 1,0,1, // v2,v3
    0,0,1, 0,1,1, // v4,v5
    0,1,0, 0,0,0  //v6,v7
    }; 

GLushort Cube::indices[] =
    {
    0,1,2, 2,3,0, // front
    0,3,4, 4,5,0, // right
    0,5,6, 6,1,0, // top
    1,6,7, 7,2,1, // left
    7,4,3, 3,2,7, // bottom
    4,7,6, 6,5,4 }; // back
#pragma endregion

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
	
}

void Cube::Draw()
{
	DrawCube();
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

void Cube::DrawIndexedCube()
{
	glPushMatrix();
	glRotatef(rotationCube, 1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	{
		for (int inc = 0; inc < 36; inc++)
		{

			//glColor3f(0.5, 0.5, 1);
			glColor3f(indexedColors[indices[inc]].r, indexedColors[indices[inc]].g,indexedColors[indices[inc]].b);
			glVertex3f(indexedVertices[indices[inc]].x, indexedVertices[indices[inc]].y, indexedVertices[indices[inc]].z);
		}
	}
	glEnd();
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
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
