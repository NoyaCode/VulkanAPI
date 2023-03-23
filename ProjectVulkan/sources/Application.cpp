#include "Application.hpp"

void Application::Create()
{
	if(!instance)
		instance = new Application();
}

void Application::Destroy()
{
	delete instance;
}

Application& Application::Get()
{
	return *instance;
}

void Application::Init(const char* windowName, int width, int height)
{
	window = new Window();
	window->Create(windowName, width, height);

	engine = new Engine();
	engine->Awake();
	engine->Start();
}

void Application::Run(const char* windowName, int width, int height)
{
	Init(windowName, width, height);

	while (!glfwWindowShouldClose(window->Get()) && !glfwGetKey(window->Get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwPollEvents();
		engine->Update();
		Render();
	}

	vkDeviceWaitIdle(engine->GetVulkan()->GetDevice());
	Release();
}

void Application::Quit()
{
	glfwSetWindowShouldClose(window->Get(), GLFW_TRUE);
}

void Application::Release()
{
	delete engine;
	delete window;
}

void Application::Render()
{
	GetVulkan()->DrawFrame();
}

Window* Application::GetWindow()
{
	return Get().window;
}

GLFWwindow* Application::GetGLFWwindow()
{
	return Get().window->Get();
}

Engine* Application::GetEngine()
{
	return engine;
}

void Application::SetWidowResized()
{
	engine->GetVulkan()->SetFramebufferResized();
}

VulkanSetup::Instance* Application::GetVulkan()
{
	return engine->GetVulkan();
}