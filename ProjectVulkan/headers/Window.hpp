#pragma once
#include <GLFW/glfw3.h>

class Window
{
private:

	GLFWwindow* window;
	const char* name;

	int width;
	int height;

public:

	~Window();

	Window* Create(const char* windowName, int clientWidth, int clientHeight);
	void Destroy();
	GLFWwindow* Get() { return window; }

	void SetSize(const int width, const int height);
	int GetWidth() const;
	int GetHeight() const;
};