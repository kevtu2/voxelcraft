#pragma once
#include <vector>
#include "../graphics/Vertex.hpp"

// Bitmasks for face culling
#define CULL_POS_Z  1
#define CULL_NEG_Z  2
#define CULL_POS_X  4
#define CULL_NEG_X  8
#define CULL_POS_Y  16
#define CULL_NEG_Y  32

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
    static BlockType GetBlockTypeFromID(unsigned char blockID);
};