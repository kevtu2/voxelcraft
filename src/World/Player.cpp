#include "Player.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

#include "Physics/Constants.hpp"

Player::Player(int width, int height)
	: position(glm::vec3(0.0f, 300.f, 0.0f)),
	lastPosition(position),
	lookDirection(glm::vec3(-1.0f, 0.0f, 0.0f)),
	cameraSpeed(10.5f),
	cameraSensitivity(2.5f),
	FOV(45.0f),
	yaw(-90.0f),
	pitch(0.0f),
	aabb(AABB(position, 2.0f, 1.0f)), // Centre the box and move down, w/ height = 2 and width = 1
	isGrounded(false),
	velocity(glm::vec3(0.0f))
{
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(lookDirection, worldUp));
	cameraUp = glm::cross(lookDirection, cameraRight);

	projection = glm::mat4(1.0f);
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	projection = glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 512.0f);
}

glm::mat4 Player::GetViewMatrix() const
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	return glm::lookAt(position, position + lookDirection, up);
}


void Player::HandleInputControls(CameraMovement move, float deltaTime)
{
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
		velocity += flatForward * cameraSpeed;
		break;

	case C_LEFT:
		velocity += -flatRight * cameraSpeed;
		break;

	case C_BACKWARD:
		velocity += -flatForward * cameraSpeed;
		break;

	case C_RIGHT:
		velocity += flatRight * cameraSpeed;
		break;

	case C_UP:
		velocity += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
		break;
	
	case C_DOWN:
		velocity += glm::vec3(0.0f, -1.0f, 0.0f) * cameraSpeed;
		break;

	case C_JUMP:
		if (isGrounded)
		{
			velocity.y = JUMP_VEL;
			isGrounded = false;
		}
		break;
	}
}

void Player::UpdatePlayerLookAt(float deltaTime, double xPos, double yPos)
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

// Position is the AABB's position since it's used to calculate collisions.
void Player::ResetPosAfterCollision(const glm::vec3 position)
{
	this->position = position - AABB_POS_OFFSET;
	aabb.UpdatePosition(position);
}

void Player::Move(float deltaTime)
{
	position += velocity * deltaTime;
	//position.y = 50.15f;
	aabb.UpdatePosition(position + AABB_POS_OFFSET);
}

