#include "BlockMesh.hpp"

BlockMesh::BlockMesh()
	: blockType(AIR),
	texturesUsed(0)
{

}

BlockMesh::BlockMesh(BlockType blockType)
	: blockType(blockType)
{
	AssignBlockInfo(blockType);
}

void BlockMesh::AssignBlockInfo(BlockType blockType)
{
	switch (blockType) {
	case GRASS:
		// Structured as <(UP.x, UP.y), (SIDE.x, SIDE.y), (DOWN.x, DOWN.y)> if more than one textures used in texture atlas.
		// Note that the texture atlas is flipped vertically, hence the indices specified below.
		textureCoords = { 0, 15, 1, 15, 2, 15 };
		texturesUsed = 3;
		break;
	case DIRT:
		textureCoords = { 2, 15 };
		texturesUsed = 1;
		break;
	case WATER:
		textureCoords = { 0, 0 };
		texturesUsed = 1;
		break;
	case STONE:
		textureCoords = { 3, 15 };
		texturesUsed = 1;
		break;
	case SAND:
		textureCoords = { 0, 14 };
		texturesUsed = 1;
		break;
	case WOOD:
		textureCoords = { 3, 14, 2, 14, 3, 14 };
		texturesUsed = 2;
		break;
	case LEAVES:
		textureCoords = { 4, 14 };
		texturesUsed = 1;
		break;
	}
}

void BlockMesh::changeBlockType(BlockType blockType)
{
	this->blockType = blockType;
	AssignBlockInfo(blockType);
}

void BlockMesh::LoadVBO(Chunk& chunk, const glm::vec3 blockOffset, const Texture& texture)
{
	// If the block uses more than 1 texture, it's texture for the sides is the second pair (1,0)
	// located inside textureCoords vector (in Block.cpp). If the block uses only 1, the
	// texture coordinates in the texture atlas will just be the first and only pair (0)
	unsigned int currentTexCoord = (texturesUsed > 1) ? F_SIDE : 0;

	// Append faces to chunk VBO -- Vertex by vertex
	for (size_t i = 0; i < 36; ++i)
	{
		// Which face is this currently drawing?
		if (i >= 24 && i <= 29)
			currentTexCoord = F_TOP;
		else if (i > 29)
			currentTexCoord = F_BOT;

		// Append vertices of the face
		unsigned int vertexIndex = CUBE_INDICES[i];

		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 0] + blockOffset.x);
		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 1] + blockOffset.y);
		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 2] + blockOffset.z);

		// Append texture coordinates

		unsigned int uvIndex = CUBE_UV_INDICES[(i % 6)];
		chunk.AppendToVBO(CUBE_UV_COORDS[uvIndex * 2 + 0] + textureCoords[currentTexCoord * 2 + 0] * SIZE_OF_TEXTURE);
		chunk.AppendToVBO(CUBE_UV_COORDS[uvIndex * 2 + 1] + textureCoords[currentTexCoord * 2 + 1] * SIZE_OF_TEXTURE);

	}
}