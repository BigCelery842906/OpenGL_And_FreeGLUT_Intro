#pragma once
#include "Camera.h"
class HelloGL;

namespace GLUTCallbacks 
{
	void Init(HelloGL* gl, Camera *cam);
	void Display();
	void Timer (int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);
	void MouseButton(int button, int state, int x, int y);
}