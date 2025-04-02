#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL/freeglut.h"
#include "Structures.h"

class Cube
{
private:
    float rotationCube;
    
    Vector3 _position;
    Vector3 _rotation;

    Mesh* _mesh;
    
public:
    Cube(Mesh* mesh, float x, float y, float z, float rotX, float rotY, float rotZ);
    ~Cube();
    void Draw();
    void Update();
    
    void DrawCube();
    void DrawIndexedCubeAlt();
    
};
