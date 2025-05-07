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

	_material = new Material();
}

Cube::~Cube()
{
	delete this;
}

void Cube::Draw()
{
	if (_mesh != nullptr)
	{
		//std::cout << "Indexed Cube method used." << std::endl;
		DrawIndexedCubeAlt();
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

void Cube::DrawIndexedCubeAlt()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &_mesh->Vertices);
	glNormalPointer(GL_FLOAT, 0, &_mesh->Normals);

	glTexCoordPointer(2,GL_FLOAT,0,&_mesh->TexCoords);

	Cube::MaterialDraw();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
	
	
	glPushMatrix();

	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(rotationCube, _rotation.x, _rotation.y, _rotation.z);

 	glDrawElements(GL_TRIANGLES, _mesh->indexCount, GL_UNSIGNED_SHORT, &_mesh->Indices);

	glPopMatrix();

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::MaterialDraw()
{
	// _material = new Material();
	_material->Ambient.x = 0.05f; _material->Ambient.y = 0.8f; _material->Ambient.z = 0.05f;
	_material->Ambient.w = 1.0f;

	_material->Diffuse.x=0.8f; _material->Diffuse.y = 0.05f; _material->Diffuse.z = 0.8f;
	_material->Diffuse.w = 1.0f;

	_material->Specular.x = 1.0f; _material->Specular.y = 1.0f; _material->Specular.z = 1.0f;
	_material->Specular.w = 1.0f;

	_material->Shininess = 1.0f;
}