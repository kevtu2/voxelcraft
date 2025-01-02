#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum CameraMovement
{
	FORWARD, BACKWARD, RIGHT, LEFT, UP, DOWN;
};

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 lookDirection;
	const glm::vec3 up; // World up vector
	const float cameraSpeed;

public:
	Camera();
	glm::mat4 GetViewMatrix() const;

	void HandleInputControls();
};