#pragma once
#include <glad\glad.h>
#include "Block.hpp"
#include <iostream>
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Texture
{
private:
	unsigned int textureID;
	unsigned int numberOfRows;
	int width, height, nrChannels;
	unsigned char* data;

	
public:
	Texture(const char* filename);
	Texture(unsigned int rows, const char* filename);
	~Texture();

	void Bind() const;
	void Unbind() const;
	unsigned int GetNumberOfRows() const { return numberOfRows; }
	void SetTextureOffset(glm::vec2 atlas, unsigned int shaderProgramID);
};