#include "CEngine.h"
#include <GLFW/glfw3.h>
#include <iostream>

CEngine::CEngine():mWindow(nullptr)
{

}

CEngine::~CEngine()
{

}

bool CEngine::initialize(int width, int height, const char * title)
{
	if (!glfwInit())
		return false;

	mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!mWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	return true;
}

void CEngine::run()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(0.1f, 0.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mWindow);

		glfwPollEvents();
	}

	glfwTerminate();
}
