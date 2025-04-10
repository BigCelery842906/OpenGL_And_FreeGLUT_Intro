#pragma once
#include "SceneObject.h"
#include <Windows.h>

class Pyramid : public SceneObject
{
private:
    float rotationPyramid;

    Vector3 _position;
    Vector3 _rotation;
    
public:
    Pyramid(Mesh* mesh, float x, float y, float z, float rotX, float rotY, float rotZ);
    ~Pyramid();
    void Update();
    void DrawPyramid();
    void Draw() override;
};
