#include "Block.hpp"



Block::Block(BlockType blockType)
	: blockType(blockType)
{
	AssignBlockInfo(blockType);
}

void Block::AssignBlockInfo(BlockType blockType)
{
	// Structured as <(UP.x, UP.y), (SIDE.x, SIDE.y), (DOWN.x, DOWN.y)> if more than one textures used in texture atlas.
	// Note that the texture atlas is flipped vertically, hence the indices specified below.

	switch (blockType) {
	case AIR:
		texturesUsed = 0;
		break;
	case GRASS:
		textureCoords = { 0, 15, 1, 15, 2, 15 };
		texturesUsed = 3;
		transparent = false;
		break;
	case DIRT:
		textureCoords = { 2, 15 };
		texturesUsed = 1;
		transparent = false;
		break;
	case WATER:
		textureCoords = { 0, 0 };
		texturesUsed = 1;
		transparent = true;
		break;
	case STONE:
		textureCoords = { 3, 15 };
		texturesUsed = 1;
		transparent = false;
		break;
	case SAND:
		textureCoords = { 0, 14 };
		texturesUsed = 1;
		transparent = false;
		break;
	case WOOD:
		textureCoords = { 3, 14, 2, 14, 3, 14 };
		texturesUsed = 2;
		transparent = false;
		break;
	case LEAVES:
		textureCoords = { 4, 14 };
		texturesUsed = 1;
		transparent = false;
		break;
	}
}


bool Block::IsTransparent(BlockType blockType)
{
	switch (blockType) {
	case AIR:
		return true;
	case GRASS:
		return false;
	case DIRT:
		return false;
	case WATER:
		return true;
	case STONE:
		return false;
	case SAND:
		return false;
	case WOOD:
		return false;
	case LEAVES:
		return true;
	}
}

BlockType Block::GetBlockTypeFromID(unsigned char blockID)
{
	if (blockID >= 0 && blockID <= 7)
		return static_cast<BlockType>(blockID);
	return AIR;
}

