#pragma once

void framebuffer_size_callback(class GLFWwindow* window, int width, int height);
class CEngine
{
public:
	CEngine();
	~CEngine();

	bool initialize(int width,int height,const char* title);
	void run();

private:

	class GLFWwindow* mWindow;

};