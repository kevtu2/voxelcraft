#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Texture will have to replace the texture coordinates in Block.hpp
// The textures will be based on a texture atlas.
// Some math needs to be done..

// For normal textures
Texture::Texture(const char* filename)
	: numberOfRows(1)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("../textures/blocks.png", &width, &height, &nrChannels, STBI_rgb);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}
}

// For texture atlas
Texture::Texture(unsigned int rows, const char* filename) 
	: Texture(filename)
{
	numberOfRows = rows;
}

Texture::~Texture()
{
	stbi_image_free(data);
	glDeleteTextures(1, &textureID);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
