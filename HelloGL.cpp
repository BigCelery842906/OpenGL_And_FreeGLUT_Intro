#include "HelloGL.h"
#include <vector>
#pragma region CubeArrays
Vertex HelloGL::vertices[] =
	{
	1, 1, 1, -1, 1, 1, -1,-1, 1, // v0-v1-v2 (front)
	-1,-1, 1, 1,-1, 1, 1, 1, 1, // v2-v3-v0
	1, 1, 1, 1,-1, 1, 1,-1,-1, // v0-v3-v4 (right)
	1,-1,-1, 1, 1,-1, 1, 1, 1, // v4-v5-v0
	1, 1, 1, 1, 1,-1, -1, 1,-1, // v0-v5-v6 (top)
	-1, 1,-1, -1, 1, 1, 1, 1, 1, // v6-v1-v0
	-1, 1, 1, -1, 1,-1, -1,-1,-1, // v1-v6-v7 (left)
	-1,-1,-1, -1,-1, 1, -1, 1, 1, // v7-v2-v1
	-1,-1,-1, 1,-1,-1, 1,-1, 1, // v7-v4-v3 (bottom)
	1,-1, 1, -1,-1, 1, -1,-1,-1, // v3-v2-v7
	1,-1,-1, -1,-1,-1, -1, 1,-1, // v4-v7-v6 (back)
	-1, 1,-1, 1, 1,-1, 1,-1,-1	// v6-v5-v4
	}; 

Color HelloGL::colors[] =
	{
	1, 1, 1, 1, 1, 0, 1, 0, 0, // v0-v1-v2 (front)
	1, 0, 0, 1, 0, 1, 1, 1, 1, // v2-v3-v0
	1, 1, 1, 1, 0, 1, 0, 0, 1, // v0-v3-v4 (right)
	0, 0, 1, 0, 1, 1, 1, 1, 1, // v4-v5-v0
	1, 1, 1, 0, 1, 1, 0, 1, 0, // v0-v5-v6 (top)
	0, 1, 0, 1, 1, 0, 1, 1, 1, // v6-v1-v0
	1, 1, 0, 0, 1, 0, 0, 0, 0, // v1-v6-v7 (left)
	0, 0, 0, 1, 0, 0, 1, 1, 0, // v7-v2-v1
	0, 0, 0, 0, 0, 1, 1, 0, 1, // v7-v4-v3 (bottom)
	1, 0, 1, 1, 0, 0, 0, 0, 0, // v3-v2-v7
	0, 0, 1, 0, 0, 0, 0, 1, 0, // v4-v7-v6 (back)
	0, 1, 0, 0, 1, 1, 0, 0, 1  // v6-v5-v4
	}; 
#pragma endregion

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

	camera-> eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	//camera-> eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera-> center.x = 0.0f; camera-> center.y = 0.0f; camera-> center.z = 0.0f;
	camera-> up.x = 0.0f; camera-> up.y = 1.0f; camera-> up.z = 0.0f;

	
	
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glEnable(GL_CULL_FACE);
	glutMainLoop();
}

void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//DrawTriangles();
	//DrawHexagon();
	//DrawCube();
	//DrawWireShapes();
	DrawCubeArray();
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
	glTranslatef(0.0f,0.0f,-5.0f);
	glTranslatef(-0.2,-0.2,-0.2);
	//glTranslatef();
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.5, 0.75);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.65, 0.5);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.35, 0.5f);
		glEnd();
	}
	
	glPopMatrix();
}

void HelloGL::DrawTriangle2()
{
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-5.0f);
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
	glTranslatef(0.0f,0.0f,-5.0f);
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
	glTranslatef(0.0f,0.0f,-5.0f);
	glTranslatef(-0.2,-0.2,-0.2);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

			glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(0.5, 0.75);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.4, 0.5f);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.85, 0.5);
		glEnd();
	}
	
	glPopMatrix();
}

void HelloGL::DrawTriangle5() 
{
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-5.0f);
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
	glTranslatef(0.0f,0.0f,-5.0f);
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
	glTranslatef(0.0f,0.0f,-5.0f);
	
	//glTranslatef(x,y,z);
	
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
	
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.3, -0.5);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.3,-0.5);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.6,0);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.3,0.5);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		glVertex2f(-0.3,0.5);
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
	glTranslatef(0.0f,0.0f,-5.0f);
	glRotatef(rotation, 1.0f, 1.0f, 1.0f);

#pragma region sugma
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
#pragma endregion
	
#pragma region CUBETIME
	glBegin(GL_POLYGON);
	glColor4f(0,0,0,0);
	glVertex3f(-0.5, -0.5, 0.5);
	glColor4f(1,0,0,0);
	glVertex3f(0.5, -0.5, 0.5);
	glColor4f(1,1,0,0);
	glVertex3f(0.5, 0.5, 0.5);
	glColor4f(0,1,0,0);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0,1,0,0);
	glVertex3f(-0.5, 0.5, 0.5);
	glColor4f(1,1,0,0);
	glVertex3f(0.5, 0.5, 0.5);
	glColor4f(0,1,1,0);
	glVertex3f(0.5, 0.5, -0.5);
	glColor4f(0,0,1,0);
	glVertex3f(-0.5, 0.5, -0.5); //minus in here
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0,0,1,0);
	glVertex3f(-0.5, 0.5, -0.5);
	glColor4f(0,1,1,0);
	glVertex3f(0.5, 0.5, -0.5);
	glColor4f(1,0,1,0);
	glVertex3f(0.5, -0.5, -0.5);
	glColor4f(1,1,1,0);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1,1,1,0);
	glVertex3f(-0.5, -0.5, -0.5);
	glColor4f(1,0,1,0);
	glVertex3f(0.5, -0.5, -0.5);
	glColor4f(1,0,0,0);
	glVertex3f(0.5, -0.5, 0.5);
	glColor4f(0,0,0,0);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1,0,0,0);
	glVertex3f(0.5, -0.5, 0.5);
	glColor4f(1,0,1,0);
	glVertex3f(0.5, -0.5, -0.5);
	glColor4f(0,1,1,0);
	glVertex3f(0.5, 0.5, -0.5);
	glColor4f(1,1,0,0);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1,1,1,0);
	glVertex3f(-0.5, -0.5,-0.5);
	glColor4f(0,0,0,0);
	glVertex3f(-0.5, -0.5, 0.5);
	glColor4f(0,1,0,0);
	glVertex3f(-0.5, 0.5, 0.5);
	glColor4f(0,0,1,0);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

#pragma endregion

	glCullFace(GL_BACK);

	
	//glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	//glutSolidCube(0.4);
	
	glPopMatrix();
}

void HelloGL::DrawWireShapes()
{
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-5.0f);
	glRotatef(rotation, 1.0f, 1.0f, 1.0f);
	
	glutWireTeapot(1);
	
	glPopMatrix();
}

void HelloGL::DrawCubeArray()
{
	glPushMatrix();
	glRotatef(rotation, 1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	for (int i =0; i < 36; i++)
	{
		glColor3fv(&colors[i].r);
		glVertex3fv(&vertices[i].x);
	}
	glEnd();

	glPopMatrix();
}

#pragma endregion


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


