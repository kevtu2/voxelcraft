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
	void CalculateTexCoord(int textureIndex[2], unsigned int texturesUsed, std::vector<float>& uvMin, std::vector<float>& uvMax);
	
};