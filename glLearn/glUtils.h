#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>

void printShaderLog(GLuint shader);

void printProgramLog(int p);

bool checkOpenglError();


/*
	read shader from opengl shader file, extension is .glsl
*/
std::string readShaderSource(const char* file);