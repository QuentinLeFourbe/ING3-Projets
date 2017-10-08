#include "stdafx.h"



#define TITLE "Hello OpenGL!"



int SCREEN_X = 1024;
int SCREEN_Y = 768;

float ax = -0.25;
float ay = 0.0;
float bx = 0.25;
float by = 0.0;
float cx = 0.0;
float cy = 0.5;
int timebase;
int frame;
int timeold;
int FPS_UPDATE = 500.0;
int angleX = 30;
int angleY = 30;
int angleZ = 30;
bool LEFT_BUTTON_STATE = false;
bool RIGHT_BUTTON_STATE = false;
bool MIDDLE_BUTTON_STATE = false;
float accRot = 0;
GLuint DrawListCube;
bool perspectiveON = false;




void drawParallelogram()
{
	glBegin(GL_QUADS);


	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(1.5, 1.118);
	glVertex2f(0.5, 1.118);

	glEnd();
}

void drawColorTriangle() {
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(ax, ay);

	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(bx, by);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(cx, cy);

	glEnd();
}


void moveColorTriangle1(int x, int y) {

	ax = (float)(x - (SCREEN_X / 2)) / (SCREEN_X / 2);
	ay = -(float)(y - (SCREEN_Y / 2)) / (SCREEN_Y / 2);
}

void moveColorTriangle2(int x, int y) {
	bx = (float)(x - (SCREEN_X / 2)) / (SCREEN_X / 2);
	by = -(float)(y - (SCREEN_Y / 2)) / (SCREEN_Y / 2);
}

void moveColorTriangle3(int x, int y) {
	cx = (float)(x - (SCREEN_X / 2)) / (SCREEN_X / 2);
	cy = -(float)(y - (SCREEN_Y / 2)) / (SCREEN_Y / 2);
}

void displayfunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawColorTriangle();
	glutSwapBuffers();
}

void keyFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'q': exit(0);
		break;
	case 27: exit(0);
		break;
	case 'p': 	
		perspectiveON = !perspectiveON;
		break;
	}
}

void mousefunc(int button, int state, int x, int y) {
	LEFT_BUTTON_STATE = false;
	RIGHT_BUTTON_STATE = false;
	MIDDLE_BUTTON_STATE = false;



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		LEFT_BUTTON_STATE = true;
		moveColorTriangle1(x, y);
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		RIGHT_BUTTON_STATE = true;
		moveColorTriangle2(x, y);
	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		MIDDLE_BUTTON_STATE = true;
		moveColorTriangle3(x, y);
	}

}


void mousefuncCube(int button, int state, int x, int y) {
	LEFT_BUTTON_STATE = false;
	RIGHT_BUTTON_STATE = false;
	MIDDLE_BUTTON_STATE = false;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		LEFT_BUTTON_STATE = true;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		RIGHT_BUTTON_STATE = true;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		MIDDLE_BUTTON_STATE = true;
	}


}

void motionfunc(int x, int y) {


	if (LEFT_BUTTON_STATE) {
		moveColorTriangle1(x, y);
	}

	if (RIGHT_BUTTON_STATE) {
		moveColorTriangle2(x, y);

	}

	if (MIDDLE_BUTTON_STATE) {
		moveColorTriangle3(x, y);
	}

}

void motionfuncCube(int x, int y) {


	if (LEFT_BUTTON_STATE) {
		angleX++;

	}

	if (RIGHT_BUTTON_STATE) {
		angleY++;

	}

	if (MIDDLE_BUTTON_STATE) {
		angleZ++;

	}

}

void idlefunc() {

	frame++;
	int timecur = glutGet(GLUT_ELAPSED_TIME);
	float bt = (float)(timecur - timebase);
	if (bt > FPS_UPDATE) {
		char t[200];
		sprintf_s(t, "%s %.0f FPS", TITLE, frame * 1000 / bt);
		glutSetWindowTitle(t);
		timebase = timecur;
		frame = 0;
	}
	timeold = timecur;

	if (LEFT_BUTTON_STATE) { angleX++; }
	if (RIGHT_BUTTON_STATE) { angleY++; }
	if (MIDDLE_BUTTON_STATE) { angleZ++; }

	
	glutPostRedisplay();

}

void reshape(GLint width, GLint height)
{
	SCREEN_X = width;
	SCREEN_Y = height;
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	

	glMatrixMode(GL_MODELVIEW);
}

void drawCube() {

	glBegin(GL_QUADS);
	//bot
	glColor3f(0.5, 0.0, 0.0);
	glVertex4f(-0.5, -0.5, -0.5, 1);
	glVertex4f(0.5, -0.5, -0.5, 1);
	glVertex4f(0.5, -0.5, 0.5, 1);
	glVertex4f(-0.5, -0.5, 0.5, 1);
	//top
	glColor3f(0.0, 0.0, 0.5);
	glVertex4f(-0.5, 0.5, -0.5, 1);
	glVertex4f(0.5, 0.5, -0.5, 1);
	glVertex4f(0.5, 0.5, 0.5, 1);
	glVertex4f(-0.5, 0.5, 0.5, 1);
	//front
	glColor3f(0.0, 0.5, 0.0);
	glVertex4f(-0.5, -0.5, -0.5, 1);
	glVertex4f(0.5, -0.5, -0.5, 1);
	glVertex4f(0.5, 0.5, -0.5, 1);
	glVertex4f(-0.5, 0.5, -0.5, 1);
	//back
	glColor3f(0.0, 0.0, 0.0);
	glVertex4f(-0.5, 0.5, 0.5, 1);
	glVertex4f(0.5, 0.5, 0.5, 1);
	glVertex4f(0.5, -0.5, 0.5, 1);
	glVertex4f(-0.5, -0.5, 0.5, 1);
	//left
	glColor3f(0.5, 0.5, 0.0);
	glVertex4f(-0.5, 0.5, 0.5, 1);
	glVertex4f(-0.5, -0.5, 0.5, 1);
	glVertex4f(-0.5, -0.5, -0.5, 1);
	glVertex4f(-0.5, 0.5, -0.5, 1);
	//right violet
	glColor3f(0.5, 0.0, 0.5);
	glVertex4f(0.5, 0.5, -0.5, 1);
	glVertex4f(0.5, 0.5, 0.5, 1);
	glVertex4f(0.5, -0.5, 0.5, 1);
	glVertex4f(0.5, -0.5, -0.5, 1);

	glEnd();

}

void displayfuncCube() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (perspectiveON) {
		gluPerspective(70, (float)SCREEN_X / SCREEN_Y, 0.1, 100);
		//gluPerspective(90.0, (float)SCREEN_X / SCREEN_Y, 1, 1000);
	}
	else {

		//glOrtho(0.0f,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_WIDTH), 0.0f, 0.0f, 1.0f);
		glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);
	}


	gluLookAt(1, 1, 1,
		0, 0, 0,
		0, 1, 0);
	glRotatef(angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);
	glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.5, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(accRot, 0.0f, 1.0f, 0.0f);
	accRot++;
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0.5);
	glutSolidSphere(0.25, 20, 20);
	glPopMatrix();

	glCallList(DrawListCube);

	glutSwapBuffers();


}

void init()
{
	timebase = 0;
	frame = 0;
	//Liste des objets
	DrawListCube = glGenLists(3);
	glNewList(DrawListCube, GL_COMPILE);
	drawCube();
	drawCube();
	glutSolidSphere(0.5, 20, 20);
	glEndList();
	glViewport(0, 0, SCREEN_X, SCREEN_Y);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(TITLE);

	init();

	glutDisplayFunc(displayfuncCube);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyFunc);
	glutMouseFunc(mousefuncCube);
	glutMotionFunc(motionfuncCube);
	glutIdleFunc(idlefunc);
	glutMainLoop();

	return 0;
}

