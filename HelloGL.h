#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"

#define REFRESHRATE 16

class HelloGL
{

private:
    float rotation;
    
public:
    
    HelloGL(int argc, char* argv[]);
    
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

    void Update();



    
    ~HelloGL(void);

};

