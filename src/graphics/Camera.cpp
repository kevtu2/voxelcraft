#include "Camera.hpp"

Camera::Camera()
	: position(glm::vec3(0.0f, 0.0f, 0.0f)),
	lookDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
	cameraSpeed(3.5f),
	cameraSensitivity(5.0f),
	yaw(-90.0f),
	pitch(0.0f)
{
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(lookDirection, worldUp));
	cameraUp = glm::cross(lookDirection, cameraRight);

	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix() const
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	return glm::lookAt(position, position + lookDirection, up);
}


void Camera::HandleInputControls(CameraMovement move, float deltaTime)
{
	switch (move) {
	case C_FORWARD:
		position += lookDirection * cameraSpeed * deltaTime;
		break;

	case C_LEFT:
		position += -cameraRight * cameraSpeed * deltaTime;
		break;

	case C_BACKWARD:
		position += -lookDirection * cameraSpeed * deltaTime;
		break;

	case C_RIGHT:
		position += cameraRight * cameraSpeed * deltaTime;
		break;
	}
}

void Camera::UpdateCameraLookAt(float deltaTime, double xPos, double yPos)
{
	xPos = xPos * cameraSensitivity * deltaTime;
	yPos = yPos * cameraSensitivity * deltaTime;

	yaw += xPos;
	pitch += yPos;

	// Prevent LookAt flip
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	lookDirection = glm::normalize(direction);

	// Update right and up vectors
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(lookDirection, up));
	cameraUp = glm::normalize(glm::cross(cameraRight, lookDirection));
}
