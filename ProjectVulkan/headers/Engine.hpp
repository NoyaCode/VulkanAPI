#pragma once

#include "VulkanSetup.hpp"
#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include <iostream>


class Engine
{
public:

	std::vector<GameObject*> objects;
	Camera camera;

private:

	VulkanSetup::Instance vulkan;

	float deltaTime = 0;
	float lastTime = 0;

public:

	~Engine();

	void Awake(); 
	void Start();
	void Update();
	void Destroy();

	void CreateResources();
	void DestroyResources();

	void CreateObjects();
	void DestroyObjects();

	void RenderObjects(const VkCommandBuffer& commandBuffer, const VkPipelineLayout& pipelineLayout, const uint32_t currentFrame);

	VulkanSetup::Instance* GetVulkan();

private:
	GameObject* AddObjects(const char* textutreName, const char* meshName, const bool willMove = true);
	void UpdateObjects();
};
