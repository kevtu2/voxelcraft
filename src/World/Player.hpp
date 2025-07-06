#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Physics/AABB.hpp"


enum CameraMovement
{
	C_FORWARD, C_BACKWARD, C_RIGHT, C_LEFT, C_UP, C_DOWN, C_JUMP, C_NONE
};

class Player
{
private:
	// TODO: Extract into Camera class
	glm::vec3 position;
	glm::vec3 lastPosition;
	glm::vec3 lookDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	const float cameraSpeed;
	float cameraSensitivity;
	float FOV;

	float yaw;
	float pitch;

	glm::mat4 projection;
	bool isGrounded;
	AABB aabb;
	glm::vec3 velocity;

public:
	Player(int width, int height);
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const { return projection; }

	void HandleInputControls(CameraMovement move, float deltaTime);
	void UpdatePlayerLookAt(float deltaTime, double xPos, double yPos);
	void ResetPosAfterCollision(const glm::vec3 position);

	inline glm::vec3 GetPlayerPosition() const { return position; }
	inline glm::vec3 GetVelocity() const { return velocity; }

	inline void SetVelocity(const glm::vec3& value) { velocity = value; }
	inline void AddVelocity(const glm::vec3& value) { velocity += value; }

	inline void SetFOV(float value) { FOV = glm::clamp(value, 1.0f, 60.0f); }
	inline void SetMouseSensitivity(float value) { cameraSensitivity = glm::clamp(value, 0.1f, 10.f); }

	void SetIsGrounded(bool value) { isGrounded = value; }
	AABB GetAABBCollision() const { return aabb; }

	void Move(float deltaTime);
};