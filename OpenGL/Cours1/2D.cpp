
#include <cstdio>
#include <cwchar>
#include <stdio.h>
#include <wchar.h>
#include <GL/glut.h>
#include <GL/gl.h>
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
bool LEFT_BUTTON_STATE = false;
bool RIGHT_BUTTON_STATE = false;
bool MIDDLE_BUTTON_STATE = false;

void init()
{
	timebase = 0;
	frame = 0;
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
	glViewport(0,0,SCREEN_X,SCREEN_Y);
}

void drawParallelogram()
{
    glBegin(GL_QUADS);

    glColor3f(0.5,0.3,0.6);

	glColor3f(1.0,0.0,0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(1.5, 1.118);
	glVertex2f(0.5, 1.118);

    glEnd();
}

void drawColorTriangle() {
	glBegin(GL_TRIANGLES);

	glColor3f(1.0,0.0,0.0);
	glVertex2f(ax,ay);

	glColor3f(0.0,1.0,0.0);
	glVertex2f(bx,by);

	glColor3f(0.0,0.0,1.0);
	glVertex2f(cx,cy);

	glEnd();
}


void moveColorTriangle1(int x, int y) {
    
    ax = (float)(x - (SCREEN_X/2)) / (SCREEN_X/2);
    ay = - (float)(y - (SCREEN_Y/2)) / (SCREEN_Y/2);
}

void moveColorTriangle2(int x, int y) {
    bx = (float)(x - (SCREEN_X/2)) / (SCREEN_X/2);
    by = - (float)(y - (SCREEN_Y/2)) / (SCREEN_Y/2);
}

void moveColorTriangle3(int x, int y) {
	cx = (float)(x - (SCREEN_X/2)) / (SCREEN_X/2);
	cy = - (float)(y - (SCREEN_Y/2)) / (SCREEN_Y/2);
}

void displayfunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawColorTriangle();
    glutSwapBuffers();
}

void keyFunc(unsigned char key, int x, int y){
	switch (key) {
		case 'q' : exit(0);
				break;
		case 27 : exit(0);
				break;
	}
}

void mousefunc(int button, int state, int x, int y){
	LEFT_BUTTON_STATE = false;
	RIGHT_BUTTON_STATE = false;
	MIDDLE_BUTTON_STATE = false;		



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		LEFT_BUTTON_STATE = true;
		moveColorTriangle1(x,y);
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
		RIGHT_BUTTON_STATE = true;
		moveColorTriangle2(x,y);
	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		MIDDLE_BUTTON_STATE = true;		
		moveColorTriangle3(x,y);
	}
}

void motionfunc(int x, int y) {
	

	if (LEFT_BUTTON_STATE) {
		moveColorTriangle1(x,y);
	}

	if (RIGHT_BUTTON_STATE){
		moveColorTriangle2(x,y);

	}

	if (MIDDLE_BUTTON_STATE){
		moveColorTriangle3(x,y);
	}

}

void idlefunc() {
	
	frame++;
	int timecur = glutGet(GLUT_ELAPSED_TIME);
	float bt = (float)(timecur - timebase);
	if (bt > FPS_UPDATE) {
		char t[200];
		sprintf(t, "%s %.0f FPS", TITLE, frame * 1000 / bt);
		glutSetWindowTitle(t);
		timebase = timecur;
		frame = 0;
	}	
	timeold = timecur;

	glutPostRedisplay();

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutCreateWindow(TITLE);
	init();
	glutKeyboardFunc(keyFunc);
	glutMouseFunc(mousefunc);
	glutMotionFunc(motionfunc);
	glutIdleFunc(idlefunc);
	glutDisplayFunc(displayfunc);
	glutMainLoop();

	return 0;
}

