#include "HelloGL.h"

#include <iostream>
#include <vector>


HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);

	rotation = 0.0f;

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

	camera = new Camera();

	camera-> eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	//camera-> eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera-> center.x = 0.0f; camera-> center.y = 0.0f; camera-> center.z = 0.0f;
	camera-> up.x = 0.0f; camera-> up.y = 1.0f; camera-> up.z = 0.0f;


	for (int i = 0; i < 200; i++)
	{
		std::cout << i << std::endl;
		cube[i] = new Cube(((rand() % 400) /10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
		//cube[i] = new Cube(i,i,i);
	}

	//cube = new Cube(1,2,3);
	
	
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glEnable(GL_CULL_FACE);
	
	glutMainLoop();
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

#pragma region DrawingPolygons
// void HelloGL::DrawPolygon() 
// {
// 	glBegin(GL_POLYGON);
// 	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
// 	glVertex2f(-0.75, 0.5);
// 	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
// 	glVertex2f(0.75, 0.5f);
// 	glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
// 	glVertex2f(0.75, -0.5);
// 	glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
// 	glVertex2f(-0.75, -0.5);
// 	glEnd();
// }
//
// #pragma region DrawTriangles
// void HelloGL::DrawTriangles()
// {
// 	DrawTriangle1();
// 	DrawTriangle2();
// 	DrawTriangle3();
// 	DrawTriangle4();
// 	DrawTriangle5();
// 	DrawTriangle6();
// 	
//
// }
//
// void HelloGL::DrawTriangle1() 
// {
// 	glPushMatrix();
// 	glTranslatef(0.0f,0.0f,-5.0f);
// 	glTranslatef(-0.2,-0.2,-0.2);
// 	//glTranslatef();
// 	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
//
// 	glBegin(GL_POLYGON);
// 	{
// 		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
// 		glVertex2f(-0.5, 0.75);
// 		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
// 		glVertex2f(-0.65, 0.5);
// 		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
// 		glVertex2f(-0.35, 0.5f);
// 		glEnd();
// 	}
// 	
// 	glPopMatrix();
// }
//
// void HelloGL::DrawTriangle2()
// {
// 	glPushMatrix();
// 	glTranslatef(0.0f,0.0f,-5.0f);
// 	glTranslatef(-0.2,-0.2,-0.2);
// 	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
//
// 	glBegin(GL_POLYGON);
// 	{
// 		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
// 		glVertex2f(-0.5, 0.2);
// 		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
// 		glVertex2f(-0.65, -0.2);
// 		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
// 		glVertex2f(-0.35, -0.2);
// 		glEnd();
// 	}
// 	
// 	glPopMatrix();
// }
//
// void HelloGL::DrawTriangle3()
// {
// 	glPushMatrix();
// 	glTranslatef(0.0f,0.0f,-5.0f);
// 	glTranslatef(-0.2,-0.2,-0.2);
// 	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
//
// 	glBegin(GL_POLYGON);
// 	{
// 		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
// 		glVertex2f(-0.5, -0.4);
// 		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
// 		glVertex2f(-0.85, -0.7);
// 		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
// 		glVertex2f(-0.4, -0.7);
// 		glEnd();
// 	}
// 	
// 	glPopMatrix();
// }
//
// void HelloGL::DrawTriangle4()
// {
// 	glPushMatrix();
// 	glTranslatef(0.0f,0.0f,-5.0f);
// 	glTranslatef(-0.2,-0.2,-0.2);
// 	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
//
// 			glBegin(GL_POLYGON);
// 	{
// 		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
// 		glVertex2f(0.5, 0.75);
// 		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
// 		glVertex2f(0.4, 0.5f);
// 		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
// 		glVertex2f(0.85, 0.5);
// 		glEnd();
// 	}
// 	
// 	glPopMatrix();
// }
//
// void HelloGL::DrawTriangle5() 
// {
// 	glPushMatrix();
// 	glTranslatef(0.0f,0.0f,-5.0f);
// 	glTranslatef(-0.2,-0.2,-0.2);
// 	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
//
// 	glBegin(GL_POLYGON);
// 	{
// 		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
// 		glVertex2f(0.4, 0.3);
// 		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
// 		glVertex2f(0.4, -0.1);
// 		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
// 		glVertex2f(0.75, -0.1f);
// 		glEnd();
// 	}
// 	
// 	glPopMatrix();
// }
//
// void HelloGL::DrawTriangle6()
// {
// 	glPushMatrix();
// 	glTranslatef(0.0f,0.0f,-5.0f);
// 	glTranslatef(-0.2,-0.2,-0.2);
// 	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
//
// 	glBegin(GL_POLYGON);
// 	{
// 		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
// 		glVertex2f(0.3, -0.3);
// 		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
// 		glVertex2f(0.45, -0.6);
// 		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
// 		glVertex2f(0.85, -0.6);
// 		glEnd();
// 	}			
// 	glPopMatrix();
// }
//
// #pragma endregion
//
// void HelloGL::DrawHexagon()
// {
// 	glPushMatrix();
// 	glTranslatef(0.0f,0.0f,-5.0f);
// 	
// 	//glTranslatef(x,y,z);
// 	
// 	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
// 	
// 	glBegin(GL_POLYGON);
// 	{
// 		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
// 		glVertex2f(-0.3, -0.5);
// 		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
// 		glVertex2f(0.3,-0.5);
// 		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
// 		glVertex2f(0.6,0);
// 		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
// 		glVertex2f(0.3,0.5);
// 		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
// 		glVertex2f(-0.3,0.5);
// 		glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
// 		glVertex2f(-0.6,0.0);
// 		glEnd();
// 	}
// 	
// 	glPopMatrix();
// 	
// }
// //https://staffsuniversity.sharepoint.com/:w:/s/TheVault/ETRXHmLlB9xOuW7OeaUxfFYBdCLU7l8f45aW5QpoQl2qKA?e=sj2DP5
//
//
//
// void HelloGL::DrawWireShapes()
// {
// 	glPushMatrix();
// 	glTranslatef(0.0f,0.0f,-5.0f);
// 	glRotatef(rotation, 1.0f, 1.0f, 1.0f);
// 	
// 	glutWireTeapot(1);
// 	
// 	glPopMatrix();
// }


#pragma endregion
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


