#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum CameraMovement
{
	FORWARD, BACKWARD, RIGHT, LEFT, UP, DOWN
};

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 lookDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	const float cameraSpeed;
	const float cameraSensitivity;

	float yaw;
	float pitch;

	glm::mat4 projection;

public:
	Camera();
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const { return projection; }

	void HandleInputControls(CameraMovement move, float deltaTime);
	void UpdateCameraLookAt(float deltaTime, double xPos, double yPos);
};