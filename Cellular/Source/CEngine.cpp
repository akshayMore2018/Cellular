#include "CEngine.h"
#include <fstream>
#include <sstream>
#include "TextureManager.h"
#include "Shader.h"
#include "Model.h"
#include "CCamera.h"

CEngine::CEngine()
	: mWindow(nullptr)
	, mBackPackModel(nullptr)
	, mVaseModel(nullptr)
	, DefaultShader(nullptr)
	, Camera(nullptr)
{

}

CEngine::~CEngine()
{
	delete mBackPackModel;
	delete mVaseModel;
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

	int AttributeCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &AttributeCount);
	C_LOG("Maximum number of vertex attributes supported :%d\n",AttributeCount);


	DefaultShader = new Shader("Source/Shaders/");
	ShaderProgram = DefaultShader->GetShaderprogramID();

	Camera = new CCamera();
	
	mBackPackModel = new Model("Source/Assets/backpack/backpack.obj");
	mVaseModel = new Model("Source/Assets/marblevase/MarbleVase0022.obj");

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
		glm::mat4 view = glm::lookAt(Camera->GetPosition(), Camera->GetPosition() + Camera->GetForwardVector(), Camera->GetUpVector());
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);



		glUseProgram(ShaderProgram);

		view = glm::lookAt(Camera->GetPosition(), Camera->GetPosition() + Camera->GetForwardVector(), Camera->GetUpVector());
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		DefaultShader->SetMat4("view", view);
		DefaultShader->SetMat4("projection", projection);


		glm::mat4 backpackmodel = glm::mat4(1.0f);
		backpackmodel = glm::translate(backpackmodel, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		backpackmodel = glm::scale(backpackmodel, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		DefaultShader->SetMat4("model", backpackmodel);
		
		mBackPackModel->Render(*DefaultShader);

		glm::mat4 vasemodel = glm::mat4(1.0f);
		vasemodel = glm::translate(vasemodel, glm::vec3(10.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		vasemodel = glm::scale(vasemodel, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
		DefaultShader->SetMat4("model", vasemodel);
		
		mVaseModel->Render(*DefaultShader);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

