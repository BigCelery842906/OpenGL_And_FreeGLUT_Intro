#include "HelloGL.h"
#include "MeshLoader.h"
#include "Pyramid.h"
#include "Texture2D.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>

#include "Camera.h"
#include "ObjLoader.h"
#include "OBJObject.h"




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
	camera = new Camera();
	
	GLUTCallbacks::Init(this, camera);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |  GLUT_DEPTH);
	
	glutInitWindowPosition(1920 - SCREEN_WIDTH, 1080 - SCREEN_HEIGHT);

	
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Basically like that one game");
	
	glutMotionFunc(GLUTCallbacks::MouseMotion);
	glutMouseFunc(GLUTCallbacks::MouseButton);
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

	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
}

void HelloGL::InitObjects()
{
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt", false);
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt", true);
	Mesh* ObjMesh = OBJ_Loader::Load((char*)"boat.obj");
	
	Texture2D* CubeTexture = new Texture2D();
	CubeTexture->Load("Penguins.raw", 512, 512);
	std::cout << "Texture pointer: " << CubeTexture << std::endl;
	std::cout << "Texture ID: " << CubeTexture->GetID() << std::endl;

	Texture2D* boatTexture = new Texture2D();
	boatTexture->Load("Boat.raw", 2048, 2048);
	std::cout << "Texture pointer: " << boatTexture << std::endl;
	std::cout << "Texture ID: " << boatTexture->GetID() << std::endl;
	
	 for (int i = 0; i < NUMOBJECTS; i++)
	 {
	 	objects[i] = new Cube(ObjMesh, boatTexture, ((rand() % 400) /10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, (rand() % 360), (rand() % 360), rand() % 360);
	 }

	// for (int i = 0; i < 200; i++)
	// {
	// 	objobject[i] = new OBJObject(ObjMesh, boatTexture, 0, 0, -50, 0, 0, 0);
	// }
	
	for (int i = NUMOBJECTS; i < 2*NUMOBJECTS; i++)
	{
		objects[i] = new Pyramid(pyramidMesh, ((rand() % 400) /10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, (rand() % 360), (rand() % 360), rand() % 360);
	}
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
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	//DRAW METHOD HERE
	 for (int i = 0; i < 2*NUMOBJECTS; i++)
	 {
	 	if (objects[i] != nullptr)
	 		objects[i]->Draw();
	 }

	for (int i = 0; i < 200; i++)
	{
		if (objobject[i] != nullptr)
		{
			objobject[i]->Draw();
		}
	}
	//DrawFloorReference();

	Vector3 v = { -1.4f, 0.7f, -1.0f};
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
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	
	// Sleep(5);
	
	for (int i = 0; i < 2*NUMOBJECTS; i++)
	{
		if (objects[i] != nullptr)
			objects[i] -> Update();
	}

	for (int i = 0; i < 200; i++)
	{
		if (objobject[i] != nullptr)
		{
			objobject[i] -> Update();
		}
	}
	
	glutPostRedisplay();
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f,0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
}

