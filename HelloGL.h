#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"

#define REFRESHRATE 16


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



class HelloGL
{

private:
    float rotation;
    
public:
    
    HelloGL(int argc, char* argv[]);
    
    

    Camera* camera;
    
    

    

    static Vertex vertices[];
    static Color colors[];

    
    void Display();
    void DrawPolygon();
    void DrawTriangles();
    void DrawTriangle1();
    void DrawTriangle2();
    void DrawTriangle3();
    void DrawTriangle4();
    void DrawTriangle5();
    void DrawTriangle6();
    void DrawHexagon();
    void DrawCube();
    void DrawWireShapes();
    void DrawCubeArray();
    void Update();
    void Keyboard(unsigned char key, int x, int y);
    
    ~HelloGL(void);

};

