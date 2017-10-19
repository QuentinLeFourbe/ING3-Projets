// OpenGL2.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"



#define BUFFER_OFFSET(offset) ((GLvoid*)(offset))

using namespace std;

int SCREEN_X = 1024;
int SCREEN_Y = 768;

glm::vec4 vertices[8] = {
	{ -0.5,-0.5,-0.5, 1.0 }, //0
	{ -0.5,-0.5, 0.5, 1.0 }, //1
	{ -0.5, 0.5,-0.5, 1.0 }, //2
	{ -0.5, 0.5, 0.5, 1.0 }, //3

	{ 0.5, 0.5, 0.5, 1.0 }, //4
	{ 0.5, 0.5,-0.5, 1.0 }, //5
	{ 0.5,-0.5, 0.5, 1.0 }, //6
	{ 0.5,-0.5,-0.5, 1.0 }  //7
};

glm::vec4 colors[8] = {
	{ 1.0,0.0,0.0,1.0 }, //red 0
	{ 1.0,1.0,0.0,1.0 }, //yellow 1
	{ 0.0,1.0,0.0,1.0 }, //green 2
	{ 0.0,0.0,1.0,1.0 }, //blue 3
	{ 1.0,0.0,1.0,1.0 }, //magenta 4
	{ 0.0,1.0,1.0,1.0 }, //cyan 5
	{ 0.0,0.0,0.0,1.0 }, //black 6
	{ 1.0,1.0,1.0,1.0 } //white 7
};

vector<glm::vec4> vPositions(36);
vector<glm::vec4> vColors(36);
GLuint vaoCube;
GLuint vboCube;

GLuint vboUniCube;
GLuint vaoUniCube;
vector<glm::vec4> vUniCube(72);

GLuint program; 
int mouseX;
int rotateX;
int mouseY;
int rotateY;
float mouseScale = 1.0;
bool LEFT_BUTTON_STATE = false;
bool RIGHT_BUTTON_STATE = false;
bool MIDDLE_BUTTON_STATE = false;





void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27: case 'q': case 'Q':
		glDeleteVertexArrays(1, &vaoCube);
		glDeleteBuffers(1, &vboCube);
		exit(EXIT_SUCCESS);
		break;
	}
}

GLchar* readShaderSource(const char * shaderFile)
{
	FILE* fp;
	fopen_s(&fp, shaderFile, "r");
	GLchar* buf;
	long size;
	if (fp == NULL) return NULL;
	fseek(fp, 0L, SEEK_END);//go to end
	size = ftell(fp);
	//get size
	fseek(fp, 0L, SEEK_SET);//go to beginning
	buf = (GLchar*)malloc((size + 1) * sizeof(GLchar));
	fread(buf, 1, size, fp);
	buf[size] = 0;
	fclose(fp);
	return buf;
}

// Create a GLSL program object from vertex and fragment shader files
GLuint initShaders(const char* vShaderFile, const char* fShaderFile)
{
	struct Shader {
		const char* filename;
		GLenum	type;
		GLchar* source;
	} shaders[2] = {
		{ vShaderFile, GL_VERTEX_SHADER, NULL },
		{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
	};

	GLuint program = glCreateProgram();

	for (int i = 0; i < 2; ++i) {
		Shader& s = shaders[i];
		s.source = readShaderSource(s.filename);
		if (shaders[i].source == NULL) {
			printf("Failed to read %s\n", s.filename);
			exit(EXIT_FAILURE);
		}

		GLuint shader = glCreateShader(s.type);
		glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			printf("%s failed to compile:\n", s.filename);
			GLint logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			printf("%s\n", logMsg);
			delete[] logMsg;
			exit(EXIT_FAILURE);
		}
		delete[] s.source;
		glAttachShader(program, shader);
	}

	/* link and error check */
	glLinkProgram(program);
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked) {
		printf("Shader program failed to link:\n");
		GLint logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		printf("%s\n", logMsg);
		delete[] logMsg;
		exit(EXIT_FAILURE);
	}

	/* use program object */
	glUseProgram(program);
	return program;

}

void updateMVP() {
	glm::mat4 Projection = glm::perspective(70.0f, (float)SCREEN_X / SCREEN_Y, 0.1f, 1000.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, (float)-1+mouseScale*0.05)); // translate, rotate
	View = glm::rotate(View, (float)rotateY*0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, (float)rotateX*0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)); // translate, rotate, scale
	glm::mat4 MVP = Projection * View * Model;
	glUniformMatrix4fv(
		glGetUniformLocation(program, "MVP"),
		1, GL_FALSE, &MVP[0][0]);
}

void updateUniMVP() {
	glm::mat4 Projection = glm::perspective(70.0f, (float)SCREEN_X / SCREEN_Y, 0.1f, 1000.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, (float)-1+mouseScale*0.05)); // translate, rotate
	View = glm::rotate(View, (float)rotateY*0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, (float)rotateX*0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)); // translate, rotate, scale
	glm::mat4 MVP = Projection * View * Model;
	glUniformMatrix4fv(
		glGetUniformLocation(program, "MVP"),
		1, GL_FALSE, &MVP[0][0]);
}

void colorCube() {

	//TOP
	vPositions.push_back(vertices[1]);
	vPositions.push_back(vertices[0]);
	vPositions.push_back(vertices[7]);
	vPositions.push_back(vertices[7]);
	vPositions.push_back(vertices[6]);
	vPositions.push_back(vertices[1]);
	//BOT
	vPositions.push_back(vertices[3]);
	vPositions.push_back(vertices[2]);
	vPositions.push_back(vertices[5]);
	vPositions.push_back(vertices[5]);
	vPositions.push_back(vertices[4]);
	vPositions.push_back(vertices[3]);
	//RIGHT
	vPositions.push_back(vertices[0]);
	vPositions.push_back(vertices[7]);
	vPositions.push_back(vertices[5]);
	vPositions.push_back(vertices[5]);
	vPositions.push_back(vertices[2]);
	vPositions.push_back(vertices[0]);
	//LEFT
	vPositions.push_back(vertices[1]);
	vPositions.push_back(vertices[3]);
	vPositions.push_back(vertices[4]);
	vPositions.push_back(vertices[4]);
	vPositions.push_back(vertices[6]);
	vPositions.push_back(vertices[1]);
	//FRONT
	vPositions.push_back(vertices[1]);
	vPositions.push_back(vertices[0]);
	vPositions.push_back(vertices[2]);
	vPositions.push_back(vertices[2]);
	vPositions.push_back(vertices[3]);
	vPositions.push_back(vertices[1]);
	//BACK
	vPositions.push_back(vertices[4]);
	vPositions.push_back(vertices[5]);
	vPositions.push_back(vertices[7]);
	vPositions.push_back(vertices[7]);
	vPositions.push_back(vertices[6]);
	vPositions.push_back(vertices[4]);


	//TOP
	vColors.push_back(colors[1]);
	vColors.push_back(colors[0]);
	vColors.push_back(colors[7]);
	vColors.push_back(colors[7]);
	vColors.push_back(colors[6]);
	vColors.push_back(colors[1]);
	//BOT
	vColors.push_back(colors[3]);
	vColors.push_back(colors[2]);
	vColors.push_back(colors[5]);
	vColors.push_back(colors[5]);
	vColors.push_back(colors[4]);
	vColors.push_back(colors[3]);
	//RIGHT
	vColors.push_back(colors[0]);
	vColors.push_back(colors[7]);
	vColors.push_back(colors[5]);
	vColors.push_back(colors[5]);
	vColors.push_back(colors[2]);
	vColors.push_back(colors[0]);
	//LEFT
	vColors.push_back(colors[1]);
	vColors.push_back(colors[3]);
	vColors.push_back(colors[4]);
	vColors.push_back(colors[4]);
	vColors.push_back(colors[6]);
	vColors.push_back(colors[1]);
	//FRONT
	vColors.push_back(colors[1]);
	vColors.push_back(colors[0]);
	vColors.push_back(colors[2]);
	vColors.push_back(colors[2]);
	vColors.push_back(colors[3]);
	vColors.push_back(colors[1]);
	//BACK
	vColors.push_back(colors[4]);
	vColors.push_back(colors[5]);
	vColors.push_back(colors[7]);
	vColors.push_back(colors[7]);
	vColors.push_back(colors[6]);
	vColors.push_back(colors[4]);



	glGenVertexArrays(1, &vaoCube);
	glBindVertexArray(vaoCube);

	glGenBuffers(1, &vboCube);
	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	int sp = vPositions.size() * sizeof(glm::vec4);
	int sc = vColors.size() * sizeof(glm::vec4);

	glBufferData(GL_ARRAY_BUFFER, sp + sc, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sp, &vPositions[0]); //load
	glBufferSubData(GL_ARRAY_BUFFER, sp, sc, &vColors[0]); // load

														   // Connect shader variables to VBO
														   // Do this after the shaders are loaded.
	GLuint vPosition =
		glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));
	GLuint vColor =
		glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(sp));

	


}

void uniCube() {

	//TOP
	vUniCube.push_back(vertices[1]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[0]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[7]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[7]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[6]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[1]);
	vUniCube.push_back(colors[3]);
	//BOT
	vUniCube.push_back(vertices[3]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[2]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[5]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[5]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[4]);
	vUniCube.push_back(colors[3]);
	vUniCube.push_back(vertices[3]);
	vUniCube.push_back(colors[3]);
	//RIGHT
	vUniCube.push_back(vertices[0]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[7]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[5]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[5]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[2]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[0]);
	vUniCube.push_back(colors[6]);
	//LEFT
	vUniCube.push_back(vertices[1]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[3]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[4]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[4]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[6]);
	vUniCube.push_back(colors[6]);
	vUniCube.push_back(vertices[1]);
	vUniCube.push_back(colors[6]);
	//FRONT
	vUniCube.push_back(vertices[1]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[0]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[2]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[2]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[3]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[1]);
	vUniCube.push_back(colors[5]);
	//BACK
	vUniCube.push_back(vertices[4]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[5]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[7]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[7]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[6]);
	vUniCube.push_back(colors[5]);
	vUniCube.push_back(vertices[4]);
	vUniCube.push_back(colors[5]);


	


	glGenVertexArrays(1, &vaoUniCube);
	glBindVertexArray(vaoUniCube);

	glGenBuffers(1, &vboUniCube);
	glBindBuffer(GL_ARRAY_BUFFER, vboUniCube);
	int sp2 = vUniCube.size() * sizeof(glm::vec4);
	
	

	glBufferData(GL_ARRAY_BUFFER, sp2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sp2, &vUniCube[0]); //load

														   // Connect shader variables to VBO
														   // Do this after the shaders are loaded.
	GLuint vPosition =
		glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT,
		GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
	GLuint vColor =
		glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT,
		GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(4 * sizeof(GLfloat)));



}


void mousefuncCube(int button, int state, int x, int y) {
	LEFT_BUTTON_STATE = false;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		LEFT_BUTTON_STATE = true;
		mouseX = x;
		mouseY = y;
		cout << x << " " << y << " " << "rotate " << rotateX << " " << rotateY << endl;
	}
	if (button == 3) {
		mouseScale++;
	}

	if (button == 4) {
		mouseScale--;
	}


}

void motionfuncCube(int x, int y) {


	if (LEFT_BUTTON_STATE) {
		rotateX += x - mouseX;
		rotateY += y - mouseY;
		mouseX = x;
		mouseY = y;
		cout << x << " " << y << " " << "rotate " << rotateX << " " << rotateY << endl;
	}

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// initiate vertex shader:
	glBindVertexArray(vaoCube);
	updateMVP();
	glDrawArrays(GL_TRIANGLES, 0, vPositions.size());


	glBindVertexArray(vaoUniCube);
	updateUniMVP();
	glDrawArrays(GL_TRIANGLES, 0, vUniCube.size());
	
	glutSwapBuffers();


}

void idlefunc() {


	glutPostRedisplay();

}

void init()
{

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	program = initShaders("MVP.vert", "cube.frag");
	colorCube();
	uniCube();

}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutCreateWindow("Color Cube");
	glewInit();
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousefuncCube);
	glutMotionFunc(motionfuncCube);
	glutIdleFunc(idlefunc);

	glutMainLoop();

	return 0;
}