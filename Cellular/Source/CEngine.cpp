#include "CEngine.h"
#include <fstream>
#include <sstream>
#include "TextureManager.h"
#include "Shader.h"
#include "Mesh.h"
#include "CCamera.h"

CEngine::CEngine()
	: mWindow(nullptr)
	, CubeMesh(nullptr)
	, DefaultShader(nullptr)
	, Camera(nullptr)
{

}

CEngine::~CEngine()
{
	delete CubeMesh;
	delete DefaultShader;
	delete Camera;
	glfwTerminate();
}

bool CEngine::Initialize(int width, int height, const char * title)
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
	{
		TextureManager::GetInstance().LoadTexture("Content/Textures/Crate.jpg");
	}
	Texture* Tex = TextureManager::GetInstance().TextureMap["Content/Textures/Crate.jpg"];
	if (Tex != nullptr)
	{
		TextureID = Tex->GetTextureID();
	}


	if (!TextureManager::GetInstance().TextureMap.count("Content/Textures/Sublime.jpg") == 1)
	{
		TextureManager::GetInstance().LoadTexture("Content/Textures/Sublime.jpg");
	}
	Tex = TextureManager::GetInstance().TextureMap["Content/Textures/Sublime.jpg"];
	if (Tex != nullptr)
	{
		TextureID2 = Tex->GetTextureID();
	}

	int AttributeCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &AttributeCount);
	C_LOG("Maximum number of vertex attributes supported :%d\n",AttributeCount);

	std::vector<Vertex> Verts
	{
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)},

		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},

		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},

		{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},

		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},

		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)}

	};


	CubeMesh = new Mesh();
	CubeMesh->InitMesh(Verts);


	DefaultShader = new Shader("Source/Shaders/");
	ShaderProgram = DefaultShader->GetShaderprogramID();

	Camera = new CCamera();
	
	
	glUseProgram(ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureID2);
	DefaultShader->SetInt("Texture1", 0);
	DefaultShader->SetInt("Texture2", 1);


	glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::rotate(Model, glm::radians(-55.0f), glm::vec3(1.0f, 0.5f, 0.0f));
	Model = glm::scale(Model, glm::vec3(1.0f, 1.0f, 1.0f));
	DefaultShader->SetMat4("model", Model);

	glm::mat4 Projection;
	Projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	DefaultShader->SetMat4("projection", Projection);
}

void CEngine::HandleEvents()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(mWindow, true);

	Camera->Events(mWindow);

}

void CEngine::Start()
{
	float LastFrame = 0.0f;
	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		float CurrentFrame = glfwGetTime();
		float DeltaTime = CurrentFrame - LastFrame;
		LastFrame = CurrentFrame;

		HandleEvents();

		Camera->Update(DeltaTime);


		glm::mat4 View = glm::mat4(1.0f);
		View = glm::lookAt(Camera->GetPosition(), Camera->GetPosition() + Camera->GetForwardVector(), Camera->GetUpVector());
		DefaultShader->SetMat4("view", View);

		CubeMesh->Render();

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

