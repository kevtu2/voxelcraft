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
			textureInfo = { 1, 0, 1, 0, 1, 0, 1, 0,  0, 0, 2, 0 };
			texturesUsed = 3;
			break;
		case DIRT:
			textureInfo = { 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0 };
			texturesUsed = 1;
			break;
		case WATER:
			textureInfo = { 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15 };
			texturesUsed = 1;
			break;
		case STONE:
			textureInfo = { 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0 };
			texturesUsed = 1;
			break;
		case SAND:
			textureInfo = { 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2 };
			texturesUsed = 1;
			break;
		case WOOD:
			textureInfo = { 2, 1, 2, 1, 2, 1, 2, 1, 3, 1, 3, 1 };
			texturesUsed = 2;
			break;
		case LEAVES:
			textureInfo = { 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1 };
			texturesUsed = 1;
			break;
	}
}
