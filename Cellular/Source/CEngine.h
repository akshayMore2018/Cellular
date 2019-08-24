#pragma once

class CEngine
{
public:
	CEngine();
	~CEngine();

	bool initialize(int width,int height,const char* title);
	void run();

private:
	class CWindow* mWindow;
};