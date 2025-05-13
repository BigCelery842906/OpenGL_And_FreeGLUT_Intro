#pragma once
#include "Structures.h"

class Camera
{
    private:
    CameraStruct camera;

    float rotation;
    int screenMiddleWidth = SCREEN_WIDTH/2;
    int screenMiddleHeight = SCREEN_HEIGHT/2;
    
    int lastX = screenMiddleWidth;
    int lastY = screenMiddleHeight;

    bool middleMouse = false;
public:
    Camera();
    ~Camera();
    void Update();
    void Keyboard(unsigned char key, int x, int y);
    void MouseMotion(int x, int y);
    void UpdateCameraFromMouse(int x, int y);
    void MouseButton(int button, int state, int x, int y);
    Vector3 CalculateMagnitudeComponents(Vector3 input, float& angle);
    Vector3 CameraCalculateForward(Vector3 center, Vector3 eye);
    Vector3 CalculateNewLookAt();
};
