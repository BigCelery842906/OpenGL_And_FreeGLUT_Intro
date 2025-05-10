#include "HelloGL.h"
#include "MeshLoader.h"
#include "Pyramid.h"
#include "Texture2D.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>

#include "ObjLoader.h"


static HelloGL* activeInstance = nullptr;

#pragma region HelloGL_Initialisation
HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitLighting();
	InitObjects();
	
	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |  GLUT_DEPTH);
	
	glutInitWindowPosition(1920 - SCREEN_WIDTH, 1080 - SCREEN_HEIGHT);

	
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Basically like that one game");
	
	glutMotionFunc(HelloGL::MouseMotion);
	glutMouseFunc(HelloGL::MouseButton);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	gluPerspective(70,SCREEN_WIDTH/SCREEN_HEIGHT,0.1,1000);
	
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	activeInstance = this;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
}

void HelloGL::InitObjects()
{
	rotation = 0.0f;

	camera = new Camera();

	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	//camera-> eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;


	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt", false);
	//Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt", true);
	OBJMesh* ObjMesh = OBJ_Loader::Load((char*)"sungerbob.obj");
	//std::cout << objMesh;
	Texture2D* texture = new Texture2D();
	texture->Load("Penguins.raw",512,512);
	std::cout << "Texture pointer: " << texture << std::endl;
	std::cout << "Texture ID: " << texture->GetID() << std::endl;
	
	for (int i = 0; i < NUMOBJECTS; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) /10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, (rand() % 360), (rand() % 360), rand() % 360);
	}
	// for (int i = NUMOBJECTS; i < 2*NUMOBJECTS; i++)
	// {
	// 	objects[i] = new Pyramid(pyramidMesh, ((rand() % 400) /10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, (rand() % 360), (rand() % 360), rand() % 360);
	// }
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0f;
	_lightPosition->y = 0.0f;
	_lightPosition->z = 0.0f;
	_lightPosition->w = 1.0f;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2f;
	_lightData->Ambient.y = 0.2f;
	_lightData->Ambient.z = 0.2f;
	_lightData->Ambient.w = 1.0f;
	_lightData->Diffuse.x = 0.8f;
	_lightData->Diffuse.y = 0.8f;
	_lightData->Diffuse.z = 0.8f;
	_lightData->Diffuse.w = 1.0f;
	_lightData->Specular.x = 0.2f;
	_lightData->Specular.y = 0.2f;
	_lightData->Specular.z = 0.2f;
	_lightData->Specular.w = 1.0f;
	
}
#pragma endregion

void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//DRAW METHOD HERE
	 for (int i = 0; i < 2*NUMOBJECTS; i++)
	 {
	 	if (objects[i] != nullptr)
	 		objects[i]->Draw();
	 }
	//DrawFloorReference();

	Vector3 v = { -1.4f, 0.7, -1.0f};
	Color c = { 0.0f,1.0f,0.0f};

	DrawString("The FitnessGram™ Pacer Test is a multistage aerobic capacity test that progressively gets more difficult as it continues. The 20 meter pacer test will begin in 30 seconds. Line up at the start. The running speed starts slowly, but gets faster each minute after you hear this signal. [beep] A single lap should be completed each time you hear this sound. [ding] Remember to run in a straight line, and run as long as possible. The second time you fail to complete a lap before the sound, your test is over. The test will begin on the word start. On your mark, get ready, start.", &v, &c);
	glFlush();
	glutSwapBuffers();
}

HelloGL::~HelloGL(void) 
{

}

// void HelloGL::DrawFloorReference()
// {
// 	glPushMatrix();
// 	glBegin(GL_POLYGON);
// 	{
// 		glColor3f(.5,0,.5);
// 		glVertex3f(10,-4,10);
// 		glVertex3f(10,-4,-10);
// 		glVertex3f(-10,-4,-10);
// 		glVertex3f(-10,-4,10);
// 	}
// 	glEnd();
// 	glPopMatrix();
// }

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	
	// Sleep(5);
	rotation += 0.5f;
	if (rotation >= 360.0f)
	{
		rotation =0.0f;
	}

	for (int i = 0; i < 2*NUMOBJECTS; i++)
	{
		if (objects[i] != nullptr)
			objects[i] -> Update();
	}
	
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	key = tolower(key); //Converts upper into lower, making sure it will always fire
	float CameraMovementSpeed = 1.0f;

	switch (key)
	{
	case 'w':
		{
			camera->center.z -= CameraMovementSpeed;
			camera->eye.z -= CameraMovementSpeed;
			break;
		}
	case 's':
		{
			camera->center.z += CameraMovementSpeed;
			camera->eye.z += CameraMovementSpeed;
			break;
		}
	case 'd':
		{
			camera->center.x += CameraMovementSpeed;
			camera->eye.x += CameraMovementSpeed;
			break;
		}
	case 'a':
		{
			camera->center.x -= CameraMovementSpeed;
			camera->eye.x -= CameraMovementSpeed;
			break;
		}
	case 'q':
		{
			camera->center.y -= CameraMovementSpeed;
			camera->eye.y -= CameraMovementSpeed;
			break;
		}
	case 15: //SHIFT???
		{
			camera->center.y -= CameraMovementSpeed;
			camera->eye.y -= CameraMovementSpeed;
			break;	
		}
	
	case 'e':
		{
			camera->center.y += CameraMovementSpeed;
			camera->eye.y += CameraMovementSpeed;
			break;
		}
	case 32:
		{
			camera->center.y += CameraMovementSpeed;
			camera->eye.y += CameraMovementSpeed;
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
void HelloGL::MouseMotion(int x, int y)
{
	if (activeInstance) //This has to be an instance otherwise it throws an error for being non-static
	{
		activeInstance->UpdateCameraFromMouse(x, y); //Pass through directly to this non-static function
		
	}
}

void HelloGL::UpdateCameraFromMouse(int x, int y)
{
	
	std::cout << "Mouse is at: " << screenMiddleWidth - x << ", " << screenMiddleHeight - y << std::endl;

	//Need to include when mouse is at edge of screens

	int deltaX = lastX - x;
	int deltaY = lastY - y;
	
	camera->eye.x += deltaX * 0.01f;
	camera->eye.y -= deltaY * 0.01f; //this is negative so it inverts and up goes up and not down.
	
	//If at edge of screen, reset the pointer but also reset last x and y to stop jittering 

	lastX = x;
	lastY = y;

}

void HelloGL::MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			std::cout << "Mouse button pressed\n";
			glutSetCursor(GLUT_CURSOR_NONE);
			activeInstance->lastX = x;
			activeInstance->lastY = y;
			
		}
		else if (state == GLUT_UP)
		{
			std::cout << "Mouse button released\n";
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
}

#pragma endregion

void CameraCalculateForward(Vector3 center, Vector3 eye);




void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f,0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
}

