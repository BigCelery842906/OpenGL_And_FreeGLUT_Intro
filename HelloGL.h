#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"

class HelloGL
{

private:
    float rotation;
    
    
public:
    
    HelloGL(int argc, char* argv[]);
    void InitGL(int argc, char* argv[]);
    void InitObjects();
    Camera* camera;

    SceneObject* objects[1000];

    void DrawFloorReference();
    void Display();
    void Update();
    void Keyboard(unsigned char key, int x, int y);
    
    ~HelloGL(void);

};

