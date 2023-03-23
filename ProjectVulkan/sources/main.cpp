#include <iostream>

#include "Window.hpp"
#include "Application.hpp"

int main() 
{
    Application::Get().Create();

    Application::Get().Run("VulkanProject", 1020, 768);

    Application::Get().Destroy();

    return 0;
}