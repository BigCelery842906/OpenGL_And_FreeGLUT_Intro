#include "HelloGL.h"
#include "MeshLoader.h"
#include "Pyramid.h"
#include "Texture2D.h"
#include <iostream>
#include <vector>
#include <Windows.h>


static HelloGL* activeInstance = nullptr;

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitObjects();	
	
	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	
	glutInitWindowPosition(1920- SCREEN_WIDTH, 1080- SCREEN_HEIGHT);

	screenMiddleWidth = SCREEN_WIDTH/2;
	screenMiddleHeight = SCREEN_HEIGHT/2;
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Basically like that one game");
	
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	gluPerspective(70,SCREEN_WIDTH/SCREEN_HEIGHT,0,1000);
	
	glMatrixMode(GL_MODELVIEW);
	
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	activeInstance = this;
	glutPassiveMotionFunc(HelloGL::MouseMotion);
	
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
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt", true);

	Texture2D* texture = new Texture2D();
	texture->Load("Penguins.raw",512,512);
	std::cout << "Texture pointer: " << texture << std::endl;
	std::cout << "Texture ID: " << texture->GetID() << std::endl;
	
	for (int i = 0; i < NUMOBJECTS; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) /10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, (rand() % 360), (rand() % 360), rand() % 360);
	}
	for (int i = NUMOBJECTS; i < 2*NUMOBJECTS; i++)
	{
		std::cout << i << std::endl;
		objects[i] = new Pyramid(pyramidMesh, ((rand() % 400) /10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, (rand() % 360), (rand() % 360), rand() % 360);
	}
}


void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//DRAW METHOD HERE
	 for (int i = 0; i < NUMOBJECTS; i++)
	 {
	 	if (objects[i] != nullptr)
	 		objects[i]->Draw();
	 }
	DrawFloorReference();
	
	glFlush();
	glutSwapBuffers();
}

HelloGL::~HelloGL(void) 
{

}

void HelloGL::DrawFloorReference()
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	{
		glColor3f(.5,0,.5);
		glVertex3f(10,-4,10);
		glVertex3f(10,-4,-10);
		glVertex3f(-10,-4,-10);
		glVertex3f(-10,-4,10);
	}
	glEnd();
	glPopMatrix();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	
	
	// Sleep(5);
	rotation += 0.5f;
	if (rotation >= 360.0f)
	{
		rotation =0.0f;
	}

	for (int i = 0; i < 400; i++)
	{
		objects[i] -> Update();
	}
	
	glutPostRedisplay();
}


void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	key = tolower(key); //Converts upper into lower, making sure it will always fire
	
	if (key == 'w')
	{
		camera->center.x -= 0.1f;
	}
	else if (key == 's')
	{
		camera->center.x += 0.1f;
	}
	else if (key == 'a')
	{
		camera->center.z += 0.1f;
	}
	else if (key == 'd')
	{
		camera->center.z -= 0.1f;
	}
	else if (key == 'q')
	{
		camera->center.y -= 0.1f;
	}
	else if (key == 'e')
	{
		camera->center.y += 0.1f;
	}
}

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

	static int lastX = screenMiddleWidth;
	static int lastY = screenMiddleHeight;

	int deltaX = lastX - x;
	int deltaY = lastY - y;
	
	camera->eye.x += deltaX * 0.01f;
	camera->eye.y -= deltaY * 0.01f; //this is negative so it inverts and up goes up and not down.

	lastX = x;
	lastY = y;
}


