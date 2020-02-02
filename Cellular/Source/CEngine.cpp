#include "CEngine.h"
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "TextureManager.h"


CEngine::CEngine():mWindow(nullptr)
{

}

CEngine::~CEngine()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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

void CEngine::InitData()
{

	glEnable(GL_DEPTH_TEST);

	if (!TextureManager::GetInstance().TextureMap.count("Content/Textures/Crate.jpg") == 1)
		TextureManager::GetInstance().LoadTexture("Content/Textures/Crate.jpg");
	Texture* Tex = TextureManager::GetInstance().TextureMap["Content/Textures/Crate.jpg"];
	if(Tex!=nullptr)
	TextureID = Tex->GetTextureID();


	if (!TextureManager::GetInstance().TextureMap.count("Content/Textures/Sublime.jpg") == 1)
		TextureManager::GetInstance().LoadTexture("Content/Textures/Sublime.jpg");
	Tex = TextureManager::GetInstance().TextureMap["Content/Textures/Sublime.jpg"];
	if (Tex != nullptr)
		TextureID2 = Tex->GetTextureID();


	int AttributeCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &AttributeCount);
	C_LOG("Maximum number of vertex attributes supported :%d\n",AttributeCount);


	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);// Bind the VAO and any subsequent vertex attribute calls from this point on will be stored inside the VAO.

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	//position attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//texture attrib
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	

	Shader BasicShader = Shader("Source/Shaders/");
	ShaderProgram = BasicShader.GetShaderprogramID();
	glUseProgram(ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureID2);
	BasicShader.SetInt("Texture1", 0);
	BasicShader.SetInt("Texture2", 1);


	glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);


	glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::rotate(Model, glm::radians(-55.0f), glm::vec3(1.0f, 0.5f, 0.0f));
	

	glm::mat4 View = glm::mat4(1.0f);
	View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f));


	glm::mat4 Projection;
	Projection = glm::perspective(glm::radians(45.0f), 8000.0f / 6000.0f, 0.1f, 100.0f);


	BasicShader.SetMat4("model", Model);
	BasicShader.SetMat4("view", View);
	BasicShader.SetMat4("projection", Projection);
}

void CEngine::run()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}


void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}
