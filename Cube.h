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
    static GLushort* indices;
    static Vertex* indexedVertices;
    static Color* indexedColors;

    static int numVertices, numColors, numIndices;
    
    Vector3 _position;
    
public:
    Cube(float x, float y, float z);
    ~Cube();
    void Draw();
    void Update();
    
    void DrawCube();
    void DrawIndexedCube();
    void DrawIndexedCubeAlt();

    static bool Load(const char* path);
    
};
