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

const int SCREEN_WIDTH	= 1024;
const int SCREEN_HEIGHT = 768;

class Model;
class Shader;
class CCamera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


class CEngine
{
public:
	CEngine();
	~CEngine();

	bool Initialize(int width,int height,const char* title);
	void Start();

private:
	void InitData();
	void HandleEvents();

private:
	unsigned int ShaderProgram;
	unsigned int SkyShaderProgram;
	unsigned int TextureID;
	unsigned int TextureID2;
	unsigned int TextureID3;

	unsigned int skyboxVAO;

	GLFWwindow	*mWindow;
	Model		*mBackPackModel;
	Model		*mVaseModel;
	Shader		*DefaultShader;
	Shader		*SkyboxShader;
	CCamera		*Camera;
};