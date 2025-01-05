#pragma once
#include <glad\glad.h>
#include "Block.hpp"
#include <iostream>
#include "stb_image.h"

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
	void CalculateTexCoord(std::vector<int> textureIndex, unsigned int texturesUsed, glm::vec2& uvMin, glm::vec2& uvMax);
	
};