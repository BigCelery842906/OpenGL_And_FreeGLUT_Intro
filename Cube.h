#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL/freeglut.h"
#include "SceneObject.h"

#include "Structures.h"

class Cube : public SceneObject
{
private:
    float rotationCube;
    
    Vector3 _position;
    Vector3 _rotation;
    
public:
    Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rotX, float rotY, float rotZ);
    ~Cube();
    void Draw();
    void Update();
    
    void DrawCube();
    void DrawIndexedCubeAlt();
    
};
