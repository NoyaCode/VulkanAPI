#include "Engine.hpp"
#include "Application.hpp"
#include <chrono>

using namespace Resources;

std::unordered_map<std::string, IResource*> ResourceManager::resources;

Engine::~Engine()
{
	Destroy();
}

void Engine::Awake()
{
	vulkan.Awake();
}

void Engine::Start()
{
	camera.Init();
	CreateResources();
	CreateObjects();

	vulkan.Start();
}

void Engine::Update()
{
	// Update DeltaTime
	static auto startTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	deltaTime = time - lastTime;
	lastTime = time;

	// Update Camera
	camera.Update(deltaTime);

	// Update GameObjects
	UpdateObjects();
}

void Engine::Destroy()
{
	vulkan.Destroy();
	for (GameObject* g : objects)
		delete g;
}

void Engine::CreateResources()
{
	ResourceManager::Create<Texture>("VikingTexture", "ressources/textures/viking_room.png");
	ResourceManager::Create<Texture>("ChadTexture", "ressources/textures/chad.jpg");
	ResourceManager::Create<Texture>("ChestTexture", "ressources/textures/Chest.png");

	ResourceManager::Create<Mesh>("VikingMesh", "ressources/models/viking_room.obj");
	ResourceManager::Create<Mesh>("CubeMesh", "ressources/models/cube.obj");
	ResourceManager::Create<Mesh>("ChestMesh", "ressources/models/Chest.obj");
}

void Engine::DestroyResources()
{
	ResourceManager::DeleteMap();
}

void Engine::CreateObjects()
{
	GameObject* vikingObj = AddObjects("VikingTexture", "VikingMesh", false);
	vikingObj->model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	vikingObj->model *= glm::rotate(glm::mat4(1.0f), 1.0f * glm::radians(-110.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	GameObject* cubeObj = AddObjects("ChadTexture","CubeMesh");
	cubeObj->model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.2f));
	cubeObj->model *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));

	GameObject* chestObj = AddObjects("ChestTexture", "ChestMesh");
	chestObj->model = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
	chestObj->model *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));
}

void Engine::DestroyObjects()
{
	for (GameObject* o : objects)
		o->Destroy();
}

GameObject* Engine::AddObjects(const char* textutreName, const char* meshName, const bool willMove)
{
	GameObject* newObject = new GameObject();
	objects.push_back(newObject);
	newObject->texture = ResourceManager::Get<Texture>(textutreName);
	newObject->mesh = ResourceManager::Get<Mesh>(meshName);
	newObject->SetUp();
	newObject->willMove = willMove;
	return newObject;
}

void Engine::UpdateObjects()
{
	for (GameObject* o : objects)
	{
		o->UpdateMVP(deltaTime, vulkan.GetCurrentFrame(), camera.vp);
	}
}

void Engine::RenderObjects(const VkCommandBuffer& commandBuffer, const VkPipelineLayout& pipelineLayout, const uint32_t currentFrame)
{
	for (GameObject* o : objects)
	{
		o->Render(commandBuffer, pipelineLayout, currentFrame);
	}
}

VulkanSetup::Instance* Engine::GetVulkan()
{
	return &vulkan;
}
