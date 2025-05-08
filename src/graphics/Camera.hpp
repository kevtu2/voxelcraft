#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

enum CameraMovement
{
	C_FORWARD, C_BACKWARD, C_RIGHT, C_LEFT, C_UP, C_DOWN
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
	Camera(int width, int height);
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const { return projection; }

	void HandleInputControls(CameraMovement move, float deltaTime);
	void UpdateCameraLookAt(float deltaTime, double xPos, double yPos);

	glm::vec3 GetCameraPosition() const { return position; }
};