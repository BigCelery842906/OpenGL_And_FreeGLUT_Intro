#pragma once
#include <vector>
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#include "GL/glut.h"

#define REFRESHRATE 16 //This is in ms not FPS
#define NUMOBJECTS 200 //Number of Cubes to Spawn
#define SCREEN_WIDTH 1080 //Width of Window
#define SCREEN_HEIGHT 1080 // Height of Window

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

};

struct OBJMesh
{
    std::vector<Vertex> Vertices;
    std::vector<Vector3> Normals;
    std::vector<TexCoord> TexCoords;
    std::vector<GLushort> Indices;
    int vertexCount, normalCount, TexCoordCount, indexCount;
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