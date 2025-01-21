#pragma once
#include <vector>
#include "../graphics/Vertex.hpp"


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

enum Face
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    UP,
    DOWN
};

class Block 
{
private:
    BlockType blockType;
    std::vector<int> textureCoords;
    unsigned int texturesUsed;
    bool transparent;

    void AssignBlockInfo(BlockType blockType);

public:
    Block(BlockType blockType = AIR);

    std::vector<int> GetTextureCoords() const { return textureCoords; }
    unsigned int GetTexturesUsed() const { return texturesUsed; }

    static bool IsTransparent(BlockType blockType);
};