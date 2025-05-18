#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "LightSource.hpp"

class VoxelShader : public Shader
{
public:
	VoxelShader(const char* vertexPath, const char* fragmentPath);
	void UseLightSource(LightSource light);

};