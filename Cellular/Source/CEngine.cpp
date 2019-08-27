#include "CEngine.h"
#include "CWindow.h"
#include <iostream>
#include "GL/glew.h"

CEngine::CEngine():mWindow(nullptr)
{

}

CEngine::~CEngine()
{
	delete mWindow;
}

bool CEngine::initialize(int width, int height, const char * title)
{
	mWindow = new CWindow();
	return mWindow->createWindow(width, height, title);
}

void CEngine::run()
{
	while (mWindow->isOpen())
	{
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		
		mWindow->swapBuffers();

	}
	mWindow->closeWindow();
}
