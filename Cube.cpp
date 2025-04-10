#include "Cube.h"
#include <fstream>
#include <iostream>
#include <string>

Cube::Cube(Mesh* mesh, Texture2D* Texture2D,float x, float y, float z, float rotX, float rotY, float rotZ) : SceneObject(mesh, Texture2D)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation.x = rotX;
	_rotation.y = rotY;
	_rotation.z = rotZ;
	
	rotationCube = 0.0f;
	
}

Cube::~Cube()
{
	delete this;
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->Indices != nullptr)
	{
		//std::cout << "Indexed Cube method used." << std::endl;
		DrawIndexedCubeAlt();
	}
	else
	{
		std::cerr << "Normal Cube method used, failed to get the required variables." << std::endl;
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
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);

	glTexCoordPointer(2,GL_FLOAT,0,_mesh->TexCoords);

	
	glPushMatrix();

	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(rotationCube, _rotation.x, _rotation.y, _rotation.z);

 	glDrawElements(GL_TRIANGLES, _mesh->indexCount, GL_UNSIGNED_SHORT, _mesh->Indices);

	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
