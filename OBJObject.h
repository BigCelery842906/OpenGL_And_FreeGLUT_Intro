#pragma once
#include "SceneObject.h"
#include "Structures.h"
#include "Texture2D.h"

class OBJObject
{
private:
    float localRotation;

    Vector3 _position;
    Vector3 _rotation;

    Material* _material;

    OBJMesh* _mesh;
    Texture2D* _texture;
    
public:
    OBJObject(OBJMesh* mesh, Texture2D* texture, float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
    ~OBJObject();

    void DrawObject();
    void Draw();
    void Update();

    void MaterialDraw();
    
};
