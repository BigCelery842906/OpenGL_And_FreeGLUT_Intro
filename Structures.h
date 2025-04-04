#pragma once
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#include "GL/glut.h"

#define REFRESHRATE 16 //This is in ms not FPS


struct Vector3
{
    float x,y,z;
};

struct Camera
{
    Vector3 eye,center,up;
};
struct Color
{
    GLfloat r,g,b;
};

struct Vertex
{
    GLfloat x,y,z;
};

struct TexCoord
{
    GLfloat u,v;
};

struct Mesh
{
    Vertex* Vertices;
    Color* Colors;
    GLushort* Indices;
    int vertexCount, colorCount, indexCount, TexCoordCount;
    TexCoord* TexCoords;
};