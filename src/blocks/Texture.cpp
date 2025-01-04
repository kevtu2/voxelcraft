#include "Texture.hpp"

// Texture will have to replace the texture coordinates in Block.hpp
// The textures will be based on a texture atlas.
// Some math needs to be done..

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
