#pragma once
#include <glad\glad.h>
#include "Block.hpp"
#define STB_IMAGE_IMPLEMENTATION
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
	Texture(unsigned int rows, const char* filename) : Texture(filename);
	~Texture();

	void Bind() const;
	void Unbind() const;
	unsigned int GetNumberOfRows() const { return numberOfRows; }
	void CalculateTexCoord(Block block);
	
};