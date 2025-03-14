#include "HelloGL.h"

#include <vector>


HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	rotation = 0.0f;
	
	glutInitWindowSize(800, 800);
	glutCreateWindow("OpenGL and FreeGLUT");
	
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	
	glutMainLoop();
}

void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawTriangles();
	DrawHexagon();
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

#pragma region DrawTriangles
void HelloGL::DrawTriangles()
{
	DrawTriangle1();
	DrawTriangle2();
	DrawTriangle3();
	DrawTriangle4();
	DrawTriangle5();
	DrawTriangle6();
	

}

void HelloGL::DrawTriangle1() 
{
	glPushMatrix();
	glTranslatef(-0.2,-0.2,-0.2);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.5, 0.75);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.35, 0.5f);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.65, 0.5);
		glEnd();
	}
	
	glPopMatrix();
}

void HelloGL::DrawTriangle2()
{
	glPushMatrix();
	glTranslatef(-0.2,-0.2,-0.2);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.5, 0.2);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.65, -0.2);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.35, -0.2);
		glEnd();
	}
	
	glPopMatrix();
}

void HelloGL::DrawTriangle3()
{
	glPushMatrix();
	glTranslatef(-0.2,-0.2,-0.2);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.5, -0.4);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.85, -0.7);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.4, -0.7);
		glEnd();
	}
	
	glPopMatrix();
}

void HelloGL::DrawTriangle4()
{
	glPushMatrix();
	glTranslatef(-0.2,-0.2,-0.2);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

			glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(0.5, 0.75);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.85, 0.5);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.4, 0.5f);
		glEnd();
	}
	
	glPopMatrix();
}

void HelloGL::DrawTriangle5() 
{
	glPushMatrix();
	glTranslatef(-0.2,-0.2,-0.2);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(0.4, 0.3);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.4, -0.1);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.75, -0.1f);
		glEnd();
	}
	
	glPopMatrix();
}

void HelloGL::DrawTriangle6()
{
	glPushMatrix();
	glTranslatef(-0.2,-0.2,-0.2);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(0.3, -0.3);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.45, -0.6);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.85, -0.6);
		glEnd();
	}			
	glPopMatrix();
}

#pragma endregion

void HelloGL::DrawHexagon()
{
	glPushMatrix();
	
	//glTranslatef(x,y,z);
	
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.3, 0.5);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.3,0.5);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.6,0);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.3,-0.5);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		glVertex2f(-0.3,-0.5);
		glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
		glVertex2f(-0.6,0.0);
		glEnd();
	}
	
	glPopMatrix();
	
}
//https://staffsuniversity.sharepoint.com/:w:/s/TheVault/ETRXHmLlB9xOuW7OeaUxfFYBdCLU7l8f45aW5QpoQl2qKA?e=sj2DP5

void HelloGL::Update()
{
	rotation += 0.5f;
	if (rotation >= 360.0f)
	{
		rotation =0.0f;
	}
	glutPostRedisplay();
}
