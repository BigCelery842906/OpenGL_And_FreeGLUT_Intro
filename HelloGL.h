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
    int screenMiddleWidth;
    int screenMiddleHeight;

    Vector4* _lightPosition;
    Lighting* _lightData;
public:
    
    HelloGL(int argc, char* argv[]);
    ~HelloGL(void);
    void InitGL(int argc, char* argv[]);
    void InitObjects();
    void InitLighting();

    Camera* camera;
    SceneObject* objects[1000];
    
    void Display();
    void Update();
    void Keyboard(unsigned char key, int x, int y);
    
    void static MouseMotion(int x, int y);
    void UpdateCameraFromMouse(int x, int y);

    void DrawString(const char* text, Vector3* position, Color* color);
    
};

