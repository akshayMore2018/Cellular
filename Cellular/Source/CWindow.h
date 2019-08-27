#pragma once

class CWindow
{
public:

	CWindow();
	~CWindow();

	bool createWindow(int width, int height, const char* title);

	bool isOpen();

	void swapBuffers();

	void closeWindow();

private:

	class GLFWwindow* mWindow;

};