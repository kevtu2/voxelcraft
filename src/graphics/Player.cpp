#include "Player.hpp"
#include <iostream>

Player::Player(int width, int height)
	: position(glm::vec3(0.0f, 100.f, 0.0f)),
	lastPosition(position),
	lookDirection(glm::vec3(-1.0f, 0.0f, 0.0f)),
	cameraSpeed(10.5f),
	cameraSensitivity(0.1f),
	yaw(-90.0f),
	pitch(0.0f),
	aabb(AABB(position, 2.0f, 1.0f)), // Centre the box and move down, w/ height = 2 and width = 1
	isColliding(false),
	velocity(glm::vec3(0.0f))
{
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(lookDirection, worldUp));
	cameraUp = glm::cross(lookDirection, cameraRight);

	projection = glm::mat4(1.0f);
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 512.0f);
}

glm::mat4 Player::GetViewMatrix() const
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	return glm::lookAt(position, position + lookDirection, up);
}


void Player::HandleInputControls(CameraMovement move, float deltaTime)
{
	if (isColliding) return;
	std::cout << "Moving.." << std::endl;

	lastPosition = position;

	// Flatten lookDirection and cameraRight onto XZ plane
	glm::vec3 flatForward = lookDirection;
	flatForward.y = 0.0f;
	flatForward = glm::normalize(flatForward);

	glm::vec3 flatRight = cameraRight;
	flatRight.y = 0.0f;
	flatRight = glm::normalize(flatRight);


	switch (move) {
	case C_FORWARD:
		velocity = flatForward * cameraSpeed;
		break;

	case C_LEFT:
		velocity = -flatRight * cameraSpeed;
		break;

	case C_BACKWARD:
		velocity = -flatForward * cameraSpeed;
		break;

	case C_RIGHT:
		velocity = flatRight * cameraSpeed;
		break;
	}
	position += velocity * deltaTime;

	position.y = 50.0f;
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
	aabb.UpdatePosition(position);
}

