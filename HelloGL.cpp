#include "HelloGL.h"
#include "MeshLoader.h"

#include <iostream>
#include <vector>


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
	
	glutInitWindowPosition(1000,100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Basically like that one game");
	
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0,0,800,800);
	gluPerspective(70,1,0,1000);
	
	glMatrixMode(GL_MODELVIEW);
	
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glEnable(GL_CULL_FACE);
}

void HelloGL::InitObjects()
{
	rotation = 0.0f;

	camera = new Camera();

	camera-> eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	//camera-> eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera-> center.x = 0.0f; camera-> center.y = 0.0f; camera-> center.z = 0.0f;
	camera-> up.x = 0.0f; camera-> up.y = 1.0f; camera-> up.z = 0.0f;


	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	for (int i = 0; i < 200; i++)
	{
		std::cout << i << std::endl;
		cube[i] = new Cube(cubeMesh, ((rand() % 400) /10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, (rand() % 360), (rand() % 360), rand() % 360);
	}
}


void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//DRAW METHOD HERE
	 for (int i = 0; i < 200; i++)
	 {
	 	cube[i] -> Draw();
	 }

	DrawFloorReference();
	//glEnd();
	
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
	
	
	Sleep(5);
	rotation += 0.5f;
	if (rotation >= 360.0f)
	{
		rotation =0.0f;
	}
	glutPostRedisplay();

	for (int i = 0; i < 200; i++)
	{
		cube[i] -> Update();
	}
	
}


void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	key = tolower(key); //Converts upper into lower, making sure it will always fire
	if (key == 'w')
	{
		camera-> center.x -= 0.1f;
	}
	else if (key == 's')
	{
		camera-> center.x += 0.1f;
	}
	else if (key == 'a')
	{
		camera-> center.z += 0.1f;
	}
	else if (key == 'd')
	{
		camera-> center.z -= 0.1f;
	}
	else if (key == 'q')
	{
		camera-> center.y -= 0.1f;
	}
	else if (key == 'e')
	{
		camera-> center.y += 0.1f;
	}
}


