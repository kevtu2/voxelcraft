#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader 
{
private:
	unsigned int programID;

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void CheckShaderCompileErrors(unsigned int shader);

	void UseProgram() const;

	unsigned int GetID() const { return programID; }
	
	void SetUniformMatrix4f(const char* name, const glm::mat4 value);
	void SetUniformVec2f(const char* name, const glm::vec2 value);
	void SetUniformVec3f(const char* name, const glm::vec3 value);
	void SetUniform1f(const char* name, const float value);
};
