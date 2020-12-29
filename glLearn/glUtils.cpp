#include "glUtils.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;

	glGetShaderiv(shader, GL_LOG_INFO_REGAL, &len);

	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);

		std::cout << "shader log: " << log << std::endl;
		free(log);
	}
	else {
		cout << "no error in shader " << endl;
	}
}


void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;

	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*) malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "program log: " << log << std::endl;
		free(log);
	}
}

bool checkOpenglError() {
	bool error = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "opengl error: " << glErr << std::endl;
		error = true;
		glErr = glGetError();
	}
	return error;
}

std::string readShaderSource(const char* file) {
	string content;
	ifstream fileStream(file, ios::in);
	string line = "";

	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}


