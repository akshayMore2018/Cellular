#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <iostream>
void framebuffer_size_callback(class GLFWwindow* window, int width, int height);
class CEngine
{
public:
	CEngine();
	~CEngine();

	bool initialize(int width,int height,const char* title);
	void run();

private:

	class GLFWwindow* mWindow;


	void InitData();

	unsigned int ShaderProgram;
	unsigned int VAO;
};