#pragma once
#include "IResource.hpp"

struct UniformBufferObject;

class GameObject
{
public:
	alignas(16) glm::mat4 mvp;
	glm::mat4 model;

	Resources::Mesh* mesh;
	Resources::Texture* texture;

	bool willMove = true;

private:
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

public:
	void SetUp();
	void UpdateMVP(const float deltatime, const uint32_t currentFrame, const glm::mat4& cameraVP);
	void Render(const VkCommandBuffer& commandBuffer, const VkPipelineLayout& pipelineLayout, const uint32_t currentFrame);
	void Destroy();

private:
	void CreateUniformBuffers();
	void CreateDescriptorPool();
	void CreateDescriptorSets();
};

