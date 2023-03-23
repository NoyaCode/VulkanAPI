#include "..\headers\Camera.hpp"
#include "..\headers\Application.hpp"

void Camera::Init()
{
	position = glm::vec3(0.0f, -3.0f, 0.5f);
	rotation = glm::vec3();

	forward = glm::vec3(0.0f, 1.0f, 0.0f);
	up = glm::vec3(0.0f, 0.0f, 1.0f);

	glfwGetCursorPos(Application::Get().GetGLFWwindow(), &lastCursorX, &lastCursorY);

	view = glm::lookAt(position, position + forward, up);
	UpdateVP();

	mustUpdate = false;
}

void Camera::Update(float deltaTime)
{
	// Activate/Desactivate Free Camera Mode
	if (IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
	{
		freeCamMode = !freeCamMode;
		if (freeCamMode) {
			glfwSetInputMode(Application::Get().GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwGetCursorPos(Application::Get().GetGLFWwindow(), &lastCursorX, &lastCursorY);
		}
		else {
			glfwSetInputMode(Application::Get().GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	if (!freeCamMode)
		return;

	UpdatePosition(deltaTime);
	UpdateRotation();

	if (mustUpdate)
	{
		view = glm::lookAt(position, position + forward, up);
		UpdateVP();
		mustUpdate = false;
	}
}

void Camera::UpdateVP()
{
	proj = glm::perspective(glm::radians(60.0f), Application::Get().GetWindow()->GetWidth() / (float)Application::Get().GetWindow()->GetHeight(), 0.1f, 400.0f);
	proj[1][1] *= -1;
	vp = proj * view;
}

void Camera::UpdatePosition(float deltaTime)
{
	float speed = moveSpeed * deltaTime;

	if (glfwGetKey(Application::Get().GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		position += forward * speed;
		mustUpdate = true;
	}

	if (glfwGetKey(Application::Get().GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= forward * speed;
		mustUpdate = true;
	}

	if (glfwGetKey(Application::Get().GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= glm::normalize(glm::cross(forward, up)) * speed;
		mustUpdate = true;
	}

	if (glfwGetKey(Application::Get().GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		position += glm::normalize(glm::cross(forward, up)) * speed;
		mustUpdate = true;
	}

	if (glfwGetKey(Application::Get().GetGLFWwindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += up * speed;
		mustUpdate = true;
	}

	if (glfwGetKey(Application::Get().GetGLFWwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		position -= up * speed;
		mustUpdate = true;
	}
}

void Camera::UpdateRotation()
{
	double xpos, ypos;
	glfwGetCursorPos(Application::Get().GetGLFWwindow(), &xpos, &ypos);

	if (xpos == lastCursorX && ypos == lastCursorY) return;

	float xoffset = xpos - lastCursorX;
	float yoffset = lastCursorY - ypos;
	lastCursorX = xpos;
	lastCursorY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	rotation.y += xoffset;
	rotation.x += yoffset;

	if (rotation.x > 89.0f)
		rotation.x = 89.0f;
	if (rotation.x < -89.0f)
		rotation.x = -89.0f;

	glm::vec3 direction;
	direction.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	direction.y = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	direction.z = sin(glm::radians(rotation.x));
	forward = glm::normalize(direction);

	mustUpdate = true;
}

bool Camera::IsMouseButtonPressed(int button)
{
	if (glfwGetMouseButton(Application::Get().GetGLFWwindow(), button) == GLFW_PRESS)
	{
		if (!isButtonHeld)
		{
			isButtonHeld = true;
			return true;
		}
		return false;
	}
	isButtonHeld = false;
	return false;
}