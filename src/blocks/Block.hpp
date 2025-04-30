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
    SOUTH, // +z
    NORTH, // -z
    EAST,  // +x
    WEST,  // -x
    UP,    // +y
    DOWN   // -y
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
    static BlockType GetBlockTypeFromID(std::byte blockID);
};