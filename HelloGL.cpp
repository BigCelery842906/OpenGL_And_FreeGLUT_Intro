#include "HelloGL.h"

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
	glutCreateWindow("OpenGL and FreeGLUT");
	
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glEnable(GL_CULL_FACE);
	glutMainLoop();
}

void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DrawTriangles();
	DrawHexagon();
	DrawCube();
	glEnd();
	
	glFlush();
	glutSwapBuffers();
}

HelloGL::~HelloGL(void) 
{

}

#pragma region DrawingPolygons
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
	//glTranslatef();
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

void HelloGL::DrawCube()
{
	glPushMatrix();

	glRotatef(rotation, 1.0f, 1.0f, 1.0f);

	/*glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex3f(-0.3,-0.3,0.3);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex3f(-0.3,0.3,0.3);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex3f(0.3,0.3,0.3);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex3f(-0.3,-0.3,0.3);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		glVertex3f(-0.3,-0.3,-0.3);
		glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
		glVertex3f(-0.3,0.3,-0.3);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex3f(0.3,0.3,-0.3);
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex3f(-0.3,-0.3,-0.3);
		glEnd();
	}*/
	
#pragma region CUBETIME
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5); //minus in here
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5, -0.5,-0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

#pragma endregion

	glCullFace(GL_BACK);

	
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	//glutSolidCube(0.4);
	
	glPopMatrix();
}

#pragma endregion

void HelloGL::Update()
{
	Sleep(5);
	rotation += 0.5f;
	if (rotation >= 360.0f)
	{
		rotation =0.0f;
	}
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
		rotation += 1.0f;
	else if (key == 'a')
		rotation -= 1.0f;
}


