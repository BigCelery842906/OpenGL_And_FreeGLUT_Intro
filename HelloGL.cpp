#include "HelloGL.h"


HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Your ass is mine Jimmy");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawTriangles();
	glEnd();
	glFlush();
}

HelloGL::~HelloGL(void) 
{

}

void HelloGL::DrawPolygon() 
{
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glVertex2f(-0.75, 0.5);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glVertex2f(0.75, 0.5f);
	glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
	glVertex2f(0.75, -0.5);
	glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
	glVertex2f(-0.75, -0.5);
	glEnd();
}

void HelloGL::DrawTriangles()
{
	DrawTriangle1();
	DrawTriangle2();
	DrawTriangle3();
	/*DrawTriangle4();
	DrawTriangle5();
	DrawTriangle6();*/

}

void HelloGL::DrawTriangle1() 
{
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glVertex2f(-0.5, 0.75);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glVertex2f(-0.35, 0.5f);
	glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
	glVertex2f(-0.65, 0.5);
	glEnd();
}

void HelloGL::DrawTriangle2()
{
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glVertex2f(-0.5, 0.2);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glVertex2f(-0.65, -0.2);
	glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
	glVertex2f(-0.35, -0.2);
	glEnd();
}

void HelloGL::DrawTriangle3()
{
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glVertex2f(-0.5, -0.4);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glVertex2f(-0.85, -0.7);
	glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
	glVertex2f(-0.4, -0.7);
	glEnd();
}

void HelloGL::DrawTriangle4()
{
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glVertex2f(0.5, 0.75);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glVertex2f(-0.85, 0.5);
	glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
	glVertex2f(-0.4, 0.5f);
	glEnd();
}

//https://staffsuniversity.sharepoint.com/:w:/s/TheVault/ETRXHmLlB9xOuW7OeaUxfFYBdCLU7l8f45aW5QpoQl2qKA?e=sj2DP5

