#include "Texture.hpp"
#include "glm/glm.hpp"

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


// Assuming our texture atlas is 16x16, in a 256x256 px png file.
void Texture::CalculateTexCoord(std::vector<int> textureIndex, unsigned int texturesUsed, glm::vec2& uvMin, glm::vec2& uvMax)
{
	/*glm::vec2 uvMin;
	glm::vec2 uvMax;
	std::vector<int> atlasCoords = block.GetTextureInfo();
	unsigned int texturesToUse = block.GetTexturesUsed();*/

}

