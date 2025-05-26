#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "AABB.hpp"

enum CameraMovement
{
	C_FORWARD, C_BACKWARD, C_RIGHT, C_LEFT, C_UP, C_DOWN, C_NONE
};

class Player
{
private:
	glm::vec3 position;
	glm::vec3 lastPosition;
	glm::vec3 lookDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	const float cameraSpeed;
	const float cameraSensitivity;

	float yaw;
	float pitch;

	glm::mat4 projection;

	AABB aabb;
	glm::vec3 velocity;

public:
	Player(int width, int height);
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const { return projection; }

	void HandleInputControls(CameraMovement move, float deltaTime);
	void UpdatePlayerLookAt(float deltaTime, double xPos, double yPos);
	void ResetPosAfterCollision(const glm::vec3 position);

	glm::vec3 GetPlayerPosition() const { return position; }
	glm::vec3 GetVelocity() const { return velocity; }
	void SetVelocity(const glm::vec3& value) { velocity = value; }
	AABB GetAABBCollision() const { return aabb; }
};