#include "VoxelShader.hpp"

VoxelShader::VoxelShader(const char* vertexPath, const char* fragmentPath) :
	Shader(vertexPath, fragmentPath)
{
}

void VoxelShader::UseLightSource(LightSource light)
{
	SetUniformVec3f("lightColor", light.GetLightColor());
	SetUniform1f("ambientIntensity", AMBIENT);
	SetUniform1f("specularIntensity", SPECULAR);
	SetUniformVec3f("lightPosition", light.GetLightPosition());
}
