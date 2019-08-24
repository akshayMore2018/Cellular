#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <cmath>
#define LOG(x) std::cout<<x<<std::endl;

const int WIDTH = 640;
const int HEIGHT = 480;
const char* TITLE = "OpenGL";

int main()
{
	if (!glfwInit())
	{
		LOG("Failed to initialize GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (window == NULL)
	{
		LOG("Window creation failed");
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		LOG("Failed to initialize GLEW");
		return -1;
	}

	glfwSwapInterval(1);
	glViewport(0, 0, WIDTH, HEIGHT);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.4f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
