#pragma once
#include "Block.hpp"
#include "Texture.hpp"
#include "Chunk.hpp"
#include "../graphics/Shader.hpp"
#include <glm/glm.hpp>
#include <vector>


static constexpr float sizeOfTexture = 0.0625f;

static constexpr float CUBE_VERTICES[] =
{
    // Bottom face
	0.0f, 0.0f, 1.0f,  0.0f,		0.0f,		  // Bottom-left
	1.0f, 0.0f, 1.0f,  textureSize, 0.0f,		  // Bottom-right
	1.0f, 0.0f, 0.0f,  textureSize, textureSize,  // Top-right
	0.0f, 0.0f, 0.0f,  0.0f,		textureSize,  // Top-left

	// Top face
	0.0f, 1.0f, 1.0f,  0.0f,		0.0f,		  // Bottom-left
	1.0f, 1.0f, 1.0f,  textureSize, 0.0f,		  // Bottom-right
	1.0f, 1.0f, 0.0f,  textureSize, textureSize,  // Top-right
	0.0f, 1.0f, 0.0f,  0.0f,		textureSize,  // Top-left

	// Front face
	0.0f, 0.0f, 1.0f,  0.0f,		0.0f,		  // Bottom-left
	1.0f, 0.0f, 1.0f,  textureSize, 0.0f,		  // Bottom-right
	1.0f, 1.0f, 1.0f,  textureSize, textureSize,  // Top-right
	0.0f, 1.0f, 1.0f,  0.0f,		textureSize,  // Top-left

	// Back face
	1.0f, 0.0f, 0.0f,  0.0f,		0.0f,		  // Bottom-left
	0.0f, 0.0f, 0.0f,  textureSize, 0.0f,		  // Bottom-right
	0.0f, 1.0f, 0.0f,  textureSize, textureSize,  // Top-right
	1.0f, 1.0f, 0.0f,  0.0f,		textureSize,  // Top-left

	// Left face
	0.0f, 0.0f, 0.0f,  0.0f,		0.0f,		  // Bottom-left
	0.0f, 0.0f, 1.0f,  textureSize, 0.0f,		  // Bottom-right
	0.0f, 1.0f, 1.0f,  textureSize, textureSize,  // Top-right
	0.0f, 1.0f, 0.0f,  0.0f,		textureSize,  // Top-left

	// Right face
	1.0f, 0.0f, 1.0f,  0.0f,		0.0f,		  // Bottom-left
	1.0f, 0.0f, 0.0f,  textureSize, 0.0f,		  // Bottom-right
	1.0f, 1.0f, 0.0f,  textureSize, textureSize,  // Top-right
	1.0f, 1.0f, 1.0f,  0.0f,		textureSize  // Top-left
};

static constexpr unsigned int CUBE_INDICES[] =
{
	// Bottom face
	0, 1, 2,
	2, 3, 0,

	// Top face
	4, 5, 6,
	6, 7, 4,

	// Front face
	8, 9, 10,
	10, 11, 8,

	// Back face
	12, 13, 14,
	14, 15, 12,

	// Left face
	16, 17, 18,
	18, 19, 16,

	// Right face
	20, 21, 22,
	22, 23, 20
};


// sizeOfTexture will just be multiplied by an offset to choose whichever texture that specific face uses.
//static constexpr float CUBE_UV_COORDS[] =
//{
//    0.0f,          0.0f, 
//    sizeOfTexture, 0.0f,  
//    sizeOfTexture, sizeOfTexture,  
//    0.0f,          sizeOfTexture,
//};

class BlockMesh
{
public:
    static void GenerateBlock(Chunk& chunk, const glm::vec3 blockOffset, const Block& block, const Texture& texture, const Shader& shaderProgram);
};
