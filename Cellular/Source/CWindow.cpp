#include "CWindow.h"
#include <GLFW/glfw3.h>

CWindow::CWindow()
{
}

CWindow::~CWindow()
{
}

bool CWindow::createWindow(int width, int height, const char * title)
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

bool CWindow::isOpen()
{
	return !glfwWindowShouldClose(mWindow);
}

void CWindow::swapBuffers()
{
	glfwSwapBuffers(mWindow);

	//TODO : shift glfwPollEvents elsewhere
	glfwPollEvents();
}

void CWindow::closeWindow()
{
	glfwTerminate();
}
