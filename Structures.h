#pragma once
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#include "GL/glut.h"

#define REFRESHRATE 16 //This is in ms not FPS
#define NUMOBJECTS 200 //Number of Cubes and Triangles to Spawn
#define SCREEN_WIDTH 800 //Width of Window
#define SCREEN_HEIGHT 800 // Height of Window

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
    TexCoord* TexCoords;
    GLushort* Indices;
    int vertexCount, colorCount, TexCoordCount, indexCount;
};