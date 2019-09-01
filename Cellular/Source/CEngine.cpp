#include "CEngine.h"
#include <iostream>
#define GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>

CEngine::CEngine():mWindow(nullptr)
{

}

CEngine::~CEngine()
{
	glfwTerminate();
}

bool CEngine::initialize(int width, int height, const char * title)
{
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!mWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Failed to init glew :" << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return false;
	}
	return true;
}

void CEngine::run()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(0.1f,0.0f,0.5f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mWindow);		
		glfwPollEvents();
	}
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}
