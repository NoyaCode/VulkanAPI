#include "Window.hpp"

Window::~Window()
{
	Destroy();
}

Window* Window::Create(const char* windowName, int clientWidth, int clientHeight)
{
	name = windowName;
	width = clientWidth;
	height = clientHeight;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(width, height, name, nullptr, nullptr);

	return this;
}

void Window::Destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::SetSize(const int width, const int height)
{
	this->width = width;
	this->height = height;
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}
