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
	Model = glm::rotate(Model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::scale(Model, glm::vec3(15.0f, 1.0f, 15.0f));
	DefaultShader->SetMat4("model", Model);

	glm::mat4 Projection;
	Projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	DefaultShader->SetMat4("projection", Projection);

	//Skybox related stuff

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};


	unsigned int skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	const std::vector<std::string>& faces
	{
		"Content/Textures/Skybox/Lake/right.jpg",
		"Content/Textures/Skybox/Lake/left.jpg",
		"Content/Textures/Skybox/Lake/top.jpg",
		"Content/Textures/Skybox/Lake/bottom.jpg",
		"Content/Textures/Skybox/Lake/front.jpg",
		"Content/Textures/Skybox/Lake/back.jpg"
	};
	
	TextureID3 = TextureManager::GetInstance().LoadCubeMap(faces);

	SkyboxShader = new Shader("Source/Shaders/Skybox/");
	SkyShaderProgram = SkyboxShader->GetShaderprogramID();
	
	
	glUseProgram(ShaderProgram);
	DefaultShader->SetInt("Texture1", 0);
	
	glUseProgram(SkyShaderProgram);
	SkyboxShader->SetInt("skybox", 0);

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

		 //draw skybox as last
		glDepthMask(GL_FALSE);  // change depth function so depth test passes when values are equal to depth buffer's content
		glUseProgram(SkyShaderProgram);
		view = glm::mat4(glm::mat3(view)); // remove translation from the view matrix
		SkyboxShader->SetMat4("view", view);
		SkyboxShader->SetMat4("projection", projection);
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID3);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE); // set depth function back to default



		glUseProgram(ShaderProgram);

		view = glm::lookAt(Camera->GetPosition(), Camera->GetPosition() + Camera->GetForwardVector(), Camera->GetUpVector());
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		DefaultShader->SetMat4("view", view);
		DefaultShader->SetMat4("projection", projection);
		// cubes
		glBindVertexArray(CubeMesh->GetVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

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

