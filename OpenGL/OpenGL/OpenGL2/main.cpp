
#include <cstdio>
#include <cwchar>
#include <stdio.h>
#include <wchar.h>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include <vector>

#define BUFFER_OFFSET(offset) ((GLvoid*)(offset))

using namespace std;

int SCREEN_X = 1024;
int SCREEN_Y = 768;

	glm::vec4 vertices[8] = {
		{-0.5,-0.5,-0.5, 1.0 }, //0
		{-0.5,-0.5, 0.5, 1.0 }, //1
		{-0.5, 0.5,-0.5, 1.0 }, //2
		{-0.5, 0.5, 0.5, 1.0 }, //3

		{ 0.5, 0.5, 0.5, 1.0 }, //4
		{ 0.5, 0.5,-0.5, 1.0 }, //5
		{ 0.5,-0.5, 0.5, 1.0 }, //6
		{ 0.5,-0.5,-0.5, 1.0 }  //7
	};

	glm::vec4 colors[8] = {
		{1.0,0.0,0.0,1.0}, //red
		{1.0,1.0,0.0,1.0}, //yellow
		{0.0,1.0,0.0,1.0}, //green
		{0.0,0.0,1.0,1.0}, //blue
		{1.0,0.0,1.0,1.0}, //magenta
		{0.0,1.0,1.0,1.0}, //cyan
		{0.0,0.0,0.0,1.0}, //black
		{1.0,1.0,1.0,1.0} //white
	};

	vector<glm::vec4> vPositions(36);
	vector<glm::vec4> vColors(36);
GLuint vaoCube;
GLuint vboCube;
void init()
{

	glClearColor (1.0, 1.0, 1.0, 1.0);
	//glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);
	glViewport(0,0,SCREEN_X,SCREEN_Y);


}



void keyboard(unsigned char key, int x, int y)
{
	switch(key) {
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
	fp = fopen(shaderFile, "r");
	GLchar* buf;
	long size;
	if (fp == NULL) return NULL;
	fseek(fp, 0L, SEEK_END);//go to end
	size = ftell(fp);
	//get size
	fseek(fp, 0L, SEEK_SET);//go to beginning
	buf = (GLchar*)malloc((size+1)*sizeof(GLchar));
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


void colorCube (){

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
	vPositions.push_back(vertices[3]);
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
	vColors.push_back(colors[3]);
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

	
	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	int sp = vPositions.size()*sizeof(glm::vec4);
	int sc = vColors.size()*sizeof(glm::vec4);

	glBufferData(GL_ARRAY_BUFFER, sp + sc, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,0,sp, &vPositions[0]); //load
	glBufferSubData(GL_ARRAY_BUFFER, sp, sc, &vColors[0]); // load


	// Connect shader variables to VBO
	// Do this after the shaders are loaded.
	GLuint program = initShaders("cube.vert","cube.frag");
	GLuint vPosition =
	glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT,
	GL_FALSE, 0,BUFFER_OFFSET(0));
	GLuint vColor =
	glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT,
	GL_FALSE, 0, BUFFER_OFFSET(sp));


}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	colorCube();
	// initiate vertex shader:
	glDrawArrays(GL_TRIANGLES, 0, vPositions.size() );
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutCreateWindow("Color Cube");
	glewInit();
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}