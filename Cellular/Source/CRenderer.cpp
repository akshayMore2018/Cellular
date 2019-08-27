#include "CRenderer.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include <iostream>

CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
}

bool CRenderer::initialize()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Failed to init glew :" <<glewGetErrorString(err)<<std::endl;
		std::cin.get();
		return false;
	}
	return true;
}
