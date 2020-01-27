#include "CEngine.h"
#include <fstream>
#include <sstream>
#include "Shader.h"

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

	glViewport(0, 0, width, height);

	InitData();

	return true;
}

void CEngine::run()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(0.1f,0.0f,0.5f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);


		glfwSwapBuffers(mWindow);		
		glfwPollEvents();
	}
}

void CEngine::InitData()
{
	int AttributeCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &AttributeCount);
	C_LOG("Maximum number of vertex attributes supported :%d\n",AttributeCount);

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//create a buffer and bind the buffer so that this buffer is used.
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//copy the data into the bound buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	Shader BasicShader = Shader("Source/Shaders/");
	ShaderProgram = BasicShader.GetShaderprogramID();

}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}
