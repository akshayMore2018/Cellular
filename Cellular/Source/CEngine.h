#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "CLog.h"

//GLM includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
class CEngine
{
public:
	CEngine();
	~CEngine();

	bool initialize(int width,int height,const char* title);
	void run();

private:

	GLFWwindow* mWindow;


	void InitData();

	unsigned int ShaderProgram;
	unsigned int VAO , VBO , EBO;
	unsigned int TextureID;
};