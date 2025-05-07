#include "Pyramid.h"

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z, float rotX, float rotY, float rotZ) : SceneObject(mesh, nullptr)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
    _rotation.x = rotX;
    _rotation.y = rotY;
    _rotation.z = rotZ;
	
    rotationPyramid = 0.0f;
}

Pyramid::~Pyramid()
{
    delete this;
}

void Pyramid::Update()
{
    rotationPyramid = 0.0f;
}

void Pyramid::Draw()
{
    if (_mesh != nullptr)
    {
        DrawPyramid();
    }
}

void Pyramid::DrawPyramid()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &_mesh->Vertices);
    glColorPointer(3, GL_FLOAT, 0, &_mesh->Normals);

    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(rotationPyramid, _rotation.x, _rotation.y, _rotation.z);
    glDrawElements(GL_TRIANGLES, _mesh->indexCount, GL_UNSIGNED_SHORT, &_mesh->Indices);
    glPopMatrix();

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
