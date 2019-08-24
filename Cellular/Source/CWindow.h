#pragma once

class CWindow
{
public:

	CWindow();
	~CWindow();

	bool createWindow(int width, int height, const char* title);

	bool isOpen();

	void clearBuffer(float r, float g, float b, float a);

	void swapBuffers();

	void closeWindow();

private:

	class GLFWwindow* mWindow;

};