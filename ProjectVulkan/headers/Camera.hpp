#pragma once

#include "Utils.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera
{

public:
	glm::mat4 vp;

private:
	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 forward;
	glm::vec3 up;

	glm::mat4 view;
	glm::mat4 proj;

	double lastCursorX = NULL;
	double lastCursorY = NULL;

	float moveSpeed = 2.5f;

	bool freeCamMode = false;
	bool isButtonHeld = false;
	bool mustUpdate;

public:
	void Init();
	void Update(float deltaTime);
	void UpdateVP();

private:
	void UpdatePosition(float deltaTime);
	void UpdateRotation();

	bool IsMouseButtonPressed(int button);
};