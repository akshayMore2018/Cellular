#include "CEngine.h"
#include "CWindow.h"
#include <iostream>

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
		mWindow->clearBuffer(0.1f, 0.1f, 0.2f, 1.0f);
		
		mWindow->swapBuffers();

	}
	mWindow->closeWindow();
}
