#include "OBJObject.h"



OBJObject::OBJObject(OBJMesh* mesh, Texture2D* texture, float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
    _position.x = posX;
    _position.y = posY;
    _position.z = posZ;
    _rotation.x = rotX;
    _rotation.y = rotY;
    _rotation.z = rotZ;

    localRotation = 0.0f;

    _material = new Material();

    _mesh = mesh;
    _texture = texture;
}

OBJObject::~OBJObject()
{
    delete _material;
    delete _texture;
}



void OBJObject::Draw()
{
    if (_mesh != nullptr)
    {
        DrawObject();
    }
}

void OBJObject::DrawObject()
{
    glBindTexture(GL_TEXTURE_2D, _texture->GetID());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY | GL_VERTEX_ARRAY | GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &(_mesh->Vertices[0]));
    glNormalPointer(GL_FLOAT, 0, &(_mesh->Normals[0]));
    glTexCoordPointer(2, GL_FLOAT, 0, &(_mesh->TexCoords[0]));

    MaterialDraw();
    glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
    glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
    glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

    glPushMatrix();

    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(localRotation, _rotation.x, _rotation.y, _rotation.z);

    glDrawElements(GL_TRIANGLES, _mesh->indexCount, GL_UNSIGNED_SHORT, &(_mesh->Indices));

    glPopMatrix();

    glDisableClientState(GL_NORMAL_ARRAY | GL_VERTEX_ARRAY | GL_TEXTURE_COORD_ARRAY);
    
    
}

void OBJObject::Update()
{
    localRotation += 0.5f;
    if (localRotation > 360.0f)
    {
        localRotation = 0.0f;
    }
    
}

void OBJObject::MaterialDraw()
{
    _material->Ambient.x = 0.05f; _material->Ambient.y = 0.8f; _material->Ambient.z = 0.05f;
    _material->Ambient.w = 1.0f;

    _material->Diffuse.x=0.8f; _material->Diffuse.y = 0.05f; _material->Diffuse.z = 0.8f;
    _material->Diffuse.w = 1.0f;

    _material->Specular.x = 1.0f; _material->Specular.y = 1.0f; _material->Specular.z = 1.0f;
    _material->Specular.w = 1.0f;

    _material->Shininess = 1.0f;
}
