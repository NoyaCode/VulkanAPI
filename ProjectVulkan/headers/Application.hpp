#pragma once
#include "Engine.hpp"
#include "Window.hpp"

class Application
{
private:

	inline static Application* instance;
	Engine* engine = nullptr;
	Window* window = nullptr;
	

public:
	
	static void Create();
	static void Destroy();
	static Application& Get();
	void Init(const char* windowName, int width, int height);
	void Run(const char* windowName, int width, int height);
	void Quit();
	Window* GetWindow();
	GLFWwindow* GetGLFWwindow();
	Engine* GetEngine();
	void SetWidowResized();
	VulkanSetup::Instance* GetVulkan();

private:

	Application() {}

	void Release();
	void Render();
};