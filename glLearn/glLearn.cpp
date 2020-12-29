// glLearn.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glUtils.h"

#define numVAOs 1


using namespace std;


float x = 0.0f;
float y = 0.0f;
float inc = 0.05f;
float inc_y = 0.01f;

GLuint renderingProgram;

GLuint vao[numVAOs];

GLuint createShaderProgram() {
    
    const char* vshaderSource = readShaderSource("./test.glsl").c_str();
    const char* fshaderSource =
        "#version 430 \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{color = vec4(1,0.5,0.3,1);}";


    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);

    printShaderLog(vShader);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();

    printProgramLog(renderingProgram);
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram);

    x += inc;
    y += inc_y;
    if (x > 1 || x < -1) {
        inc *= -1;
    }

    if (y > 1 || y < -1) {
        inc_y *= -1;
    }

    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    GLuint offsetLocY = glGetUniformLocation(renderingProgram, "oy");
    glProgramUniform1f(renderingProgram, offsetLoc, x);
    glProgramUniform1f(renderingProgram, offsetLocY, y);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL Study", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);

    init(window);
    
    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}