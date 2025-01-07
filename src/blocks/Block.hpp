#pragma once
#include <vector>

enum BlockType
{
	AIR, // Default type
	GRASS,
	DIRT,
	WATER,
	STONE,
	SAND,
	WOOD,
	LEAVES
};


enum BlockState
{
	TRANSPARENT,
	SOLID,
	LIQUID
};

constexpr float textureSize = 0.0625f;

constexpr float BLOCK_VERTEX_DATA[] =
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

constexpr unsigned int BLOCK_VERTEX_INDICES[] =
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



struct Block
{
private:
	BlockType type;

	// textureInfo: {(UP texture index), (SIDE texture index), (BOT texture index)} -- Used for texture atlas, where texture index is (col, row).
	// By default, a value of one texture index pair means the block uses one texture
	std::vector<int> textureInfo; 
	unsigned int texturesUsed;

public:
	Block();
	Block(BlockType type);
	std::vector<int> GetTextureInfo() const { return textureInfo; }
	unsigned int GetTexturesUsed() const { return texturesUsed; }
};