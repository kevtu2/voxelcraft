#include "Texture.hpp"

// For normal textures
Texture::Texture(const char* filename)
	: numberOfRows(1)
{

}

// For texture atlas
Texture::Texture(unsigned int rows, const char* filename)
	: numberOfRows(rows)
{

}

Texture::~Texture()
{
}

void Texture::Bind() const
{
}

void Texture::Unbind() const
{
}
