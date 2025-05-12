#include "GLUTCallbacks.h"

#include "Camera.h"
#include "HelloGL.h"

namespace GLUTCallbacks
{
	namespace 
	{
		HelloGL* helloGL = nullptr;
		Camera* camera = nullptr;
	}
	void Init(HelloGL *gl, Camera *cam)
	{
		helloGL = gl;
		camera = cam;
		
	}
	void Display() 
	{
		if (helloGL != nullptr) 
		{
			helloGL->Display();
		}
	}
	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		camera->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}
	void Keyboard(unsigned char key, int x, int y)
	{
		camera->Keyboard(key,x,y);
	}

	void MouseMotion(int x, int y)
	{
		camera->MouseMotion(x,y);
	}

	void MouseButton(int button, int state, int x, int y)
	{
		camera->MouseButton(button,state,x,y);
	}
}