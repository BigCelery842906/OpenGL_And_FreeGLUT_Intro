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
    static Vertex indexedVertices[];
    static Color indexedColors[];
    static GLushort indices[];

    Vector3 _position;
public:
    Cube(float x, float y, float z);
    ~Cube();

    void Draw();
    void Update();
    
    void DrawCube();
    void DrawIndexedCube();
    void DrawIndexedCubeAlt();
    
};
