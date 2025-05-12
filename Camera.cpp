#include "Camera.h"

#include <iostream>

#include "HelloGL.h"

static Camera* activeInstance = nullptr;
Camera::Camera()
{
    rotation = 0.0f;
    
    activeInstance = this;
    
    camera = CameraStruct();
    camera.eye.x = 0.0f; camera.eye.y = 0.0f; camera.eye.z = 1.0f;
    //camera-> eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
    camera.center.x = 0.0f; camera.center.y = 0.0f; camera.center.z = 0.0f;
    camera.up.x = 0.0f; camera.up.y = 1.0f; camera.up.z = 0.0f;
}

Camera::~Camera()
{
    std::cout << "Balls" << std::endl;
}

void Camera::Update()
{
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);

    rotation += 0.5f;
    if (rotation >= 360.0f)
    {
        rotation =0.0f;
    }

}

void Camera::Keyboard(unsigned char key, int x, int y)
{
    key = tolower(key); //Converts upper into lower, making sure it will always fire
    float CameraMovementSpeed = 1.0f;

    switch (key)
    {
    case 'w':
        {
            camera.center.z -= CameraMovementSpeed;
            camera.eye.z -= CameraMovementSpeed;
            break;
        }
    case 's':
        {
            camera.center.z += CameraMovementSpeed;
            camera.eye.z += CameraMovementSpeed;
            break;
        }
    case 'd':
        {
            camera.center.x += CameraMovementSpeed;
            camera.eye.x += CameraMovementSpeed;
            break;
        }
    case 'a':
        {
            camera.center.x -= CameraMovementSpeed;
            camera.eye.x -= CameraMovementSpeed;
            break;
        }
    case 'q':
        {
            camera.center.y -= CameraMovementSpeed;
            camera.eye.y -= CameraMovementSpeed;
            break;
        }
    case 'c': //SHIFT /CTRL ???
        {
            camera.center.y -= CameraMovementSpeed;
            camera.eye.y -= CameraMovementSpeed;
            break;	
        }
	
    case 'e':
        {
            camera.center.y += CameraMovementSpeed;
            camera.eye.y += CameraMovementSpeed;
            break;
        }
    case 32:
        {
            camera.center.y += CameraMovementSpeed;
            camera.eye.y += CameraMovementSpeed;
            break;
        }
    case 27:
        {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
            break;
        }
    default:
        {
            break;
        }
    }
}

// Vector3 NormalizeVector(Vector3 inputVector)
// {
// 	return Vector3(0.0f,0.0f,0.0f);
// }

#pragma region MouseCameraMovement
void Camera::MouseMotion(int x, int y)
{
    if (activeInstance) //This has to be an instance otherwise it throws an error for being non-static
    {
        activeInstance->UpdateCameraFromMouse(x, y); //Pass through directly to this non-static function
		
    }
}

void Camera::UpdateCameraFromMouse(int x, int y)
{
	
    std::cout << "Mouse is at: " << screenMiddleWidth - x << ", " << screenMiddleHeight - y << std::endl;

    //Need to include when mouse is at edge of screens

    int deltaX = lastX - x;
    rotation = deltaX;
    int deltaY = lastY - y;

    rotation *= -1;
    if (!middleMouse)
    {
        camera.eye = CalculateMagnitudeComponents(camera.eye, rotation);
    }
    //If at edge of screen, reset the pointer but also reset last x and y to stop jittering 
    camera.eye.y -= deltaY * 0.01f; //this is negative so it inverts and up goes up and not down.
    if (middleMouse)
    {
        camera.eye.x += deltaX * 0.01f;
        camera.center.x += deltaX * 0.01f;
        camera.center.y -= deltaY * 0.01f;
    }
    lastX = x;
    lastY = y;

}
void Camera::MouseButton(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) | (button == GLUT_RIGHT_BUTTON))
    {
        if (state == GLUT_DOWN)
        {
            std::cout << "Mouse button pressed\n";
            glutSetCursor(GLUT_CURSOR_NONE);
            activeInstance->lastX = x;
            activeInstance->lastY = y;
            //activeInstance->middleMouse = false;
        }
        else if (state == GLUT_UP)
        {
            std::cout << "Mouse button released\n";
            glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    if (button == GLUT_MIDDLE_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            std::cout << "Scroll button pressed\n";
            glutSetCursor(GLUT_CURSOR_NONE);
            activeInstance->lastX = x;
            activeInstance->lastY = y;
            activeInstance->middleMouse = true;
        }
	
        if (state == GLUT_UP)
			
        {
            std::cout << "Scroll Middle button released\n";
            glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
            activeInstance->middleMouse = false;
        }
    }
}

Vector3 Camera::CalculateMagnitudeComponents(Vector3 input, float &angle)
{
    if (angle > 360)
    {
        angle -= 360;
    }
    if (angle < 0)
    {
        angle += 360;
    }
    
    float radianAngle = angle * RADIANS;
    Vector3 output;
    output.x = input.x * cos(radianAngle) - input.z * sin(radianAngle);
    output.z = input.x * sin(radianAngle) + input.z * cos(radianAngle);

    

    std::cout << "Magnitude: " << output.x << ", " << output.z << std::endl;
    //angle = 0.0f;
    return output;
}

#pragma endregion

Vector3 Camera::CameraCalculateForward(Vector3 center, Vector3 eye)
{
    Vector3 forward;
    forward.x = center.x - eye.x;
    forward.y = center.y - eye.y;
    forward.z = center.z - eye.z;
    return forward;
}

