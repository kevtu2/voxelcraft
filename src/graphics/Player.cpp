#include "Player.hpp"

Player::Player(int width, int height)
	: position(glm::vec3(0.0f, 100.f, 0.0f)),
	lastPosition(position),
	lookDirection(glm::vec3(-1.0f, 0.0f, 0.0f)),
	cameraSpeed(15.5f),
	cameraSensitivity(0.1f),
	yaw(-90.0f),
	pitch(0.0f)
{
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(lookDirection, worldUp));
	cameraUp = glm::cross(lookDirection, cameraRight);

	projection = glm::mat4(1.0f);
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 512.0f);

	glm::vec3 aabbPos = position + glm::vec3(-0.5, 0, -0.5); // Centre the collision box
	aabb = AABB(aabbPos, 2, 1); // height = 2, width = 1 (block)
}

glm::mat4 Player::GetViewMatrix() const
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	return glm::lookAt(position, position + lookDirection, up);
}


void Player::HandleInputControls(CameraMovement move, float deltaTime)
{
	lastPosition = position;

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
	aabb.UpdatePosition(position);
}

void Player::UpdatePlayerLookAt(float deltaTime, double xPos, double yPos)
{
	xPos = xPos * cameraSensitivity;
	yPos = yPos * cameraSensitivity;

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

void Player::ResetPosAfterCollision(const glm::vec3 position)
{
	this->position = position;
	aabb.UpdatePosition(position + glm::vec3(-0.5, 0, -0.5));
}

