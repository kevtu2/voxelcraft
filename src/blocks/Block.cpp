#include "Block.hpp"

Block::Block()
	: type(AIR),
	texturesUsed(0)
{
	
}

Block::Block(BlockType type)
	: type(type)
{
	switch (type) {
		case GRASS:
			// Structured as <(UP.x, UP.y), (SIDE.x, SIDE.y), (DOWN.x, DOWN.y)> if more than one textures used in texture atlas.
			// Note that the texture atlas is flipped vertically, hence the indices specified below.
			textureInfo = { 0, 15, 1, 15, 2, 15 };
			texturesUsed = 3;
			break;
		case DIRT:
			textureInfo = { 2, 15 };
			texturesUsed = 1;
			break;
		case WATER:
			textureInfo = { 0, 0 };
			texturesUsed = 1;
			break;
		case STONE:
			textureInfo = { 3, 15 };
			texturesUsed = 1;
			break;
		case SAND:
			textureInfo = { 0, 14 };
			texturesUsed = 1;
			break;
		case WOOD:
			textureInfo = { 3, 14, 2, 14, 3, 14 };
			texturesUsed = 2;
			break;
		case LEAVES:
			textureInfo = { 4, 14 };
			texturesUsed = 1;
			break;
	}
}
