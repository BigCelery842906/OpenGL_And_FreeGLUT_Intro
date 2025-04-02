#pragma once

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
