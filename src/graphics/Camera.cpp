#include "Camera.hpp"

Camera::Camera()
	: position(glm::vec3(0.0f, 0.0f, 0.0f)),
	lookDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	cameraSpeed(2.5f);
{

}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(position, position + lookDirection, up);
}


