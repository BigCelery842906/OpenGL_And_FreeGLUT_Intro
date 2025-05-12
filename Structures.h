#pragma once
#include <vector>
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#include "GL/glut.h"

#define REFRESHRATE 16 //This is in ms not FPS
#define NUMOBJECTS 200 //Number of Cubes to Spawn
#define SCREEN_WIDTH 800 //Width of Window
#define SCREEN_HEIGHT 800 // Height of Window
#define PI 3.14159265
#define RADIANS (PI/180.0)

struct Vector3
{
    float x,y,z;
};

struct Vector4
{
    float x,y,z,w;
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
    Vector3* Normals;
    TexCoord* TexCoords;
    GLushort* Indices;
    int vertexCount, normalCount, TexCoordCount, indexCount;

    Mesh()
    {
        vertexCount = normalCount = TexCoordCount = indexCount = 0;
    }
};

struct Lighting
{
    Vector4 Ambient, Diffuse, Specular;
};

struct Material
{
    Vector4 Ambient, Diffuse, Specular;
    GLfloat Shininess;
};