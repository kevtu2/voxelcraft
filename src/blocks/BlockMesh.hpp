#pragma once
#include "Texture.hpp"
#include "Chunk.hpp"
#include "../graphics/Shader.hpp"
#include <glm/glm.hpp>
#include <vector>

/**
 * @file BlockMesh.hpp
 * @brief Defines and generates vertex buffer data for a given block.
 * 
 * This entire class/file consists of the necessary data to create a
 * block of a specified type. It's  state machine, meaning that it 
 * should be created once, but its state should be changed to create 
 * different blocks.
 * 
 */


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

enum Face {
    F_TOP,
    F_SIDE,
    F_BOT
};

static constexpr float SIZE_OF_TEXTURE = 0.0625f;

static constexpr float CUBE_VERTICES[] =
{
    0, 0, 0,
    1, 0, 0,
    1, 1, 0,
    0, 1, 0,

    0, 0, 1,
    1, 0, 1,
    1, 1, 1,
    0, 1, 1
};

static constexpr unsigned int CUBE_INDICES[] =
{
    1, 0, 3, 1, 3, 2, // north (-z)
    4, 5, 6, 4, 6, 7, // south (+z)
    5, 1, 2, 5, 2, 6, // east (+x)
    0, 4, 7, 0, 7, 3, // west (-x)
    2, 3, 7, 2, 7, 6, // top (+y)
    5, 4, 0, 5, 0, 1, // bottom (-y)
};


// SIZE_OF_TEXTURE will just be multiplied by an offset to choose whichever texture that specific face uses.
static constexpr float CUBE_UV_COORDS[] =
{
    0,               0,
    SIZE_OF_TEXTURE, 0,
    SIZE_OF_TEXTURE, SIZE_OF_TEXTURE,
    0,               SIZE_OF_TEXTURE,
};

static constexpr unsigned int CUBE_UV_INDICES[] = { 1, 0, 3, 1, 3, 2 };


/**
 * @struct BlockMesh
 * @brief A container class used to store and generate block data.
 * 
 * The BlockMesh class represents a state machine, meaning that it
 * should be created once, but its attributes can be changed to
 * specify which block to draw via OpenGL. Similar to OpenGL binding,
 * we can bind a block type to only draw that when performing draw calls.
 */
struct BlockMesh
{
private:
    BlockType blockType;
    std::vector<int> textureCoords;
    unsigned int texturesUsed;

    void AssignBlockInfo(BlockType blockType);

public:
    BlockMesh();
    BlockMesh(BlockType blockType);

    std::vector<int> GetTextureCoords(BlockType type) const { return textureCoords; }
    unsigned int GetTexturesUsed(BlockType type) const { return texturesUsed; }
    
    /**
     * @brief Changes the type of the current block that we want to draw.
     * 
     * @param blockType Specifies the block we currently want to draw
     */
    void changeBlockType(BlockType blockType);

     /**
     * @brief Generates vertex data depending on the block currently bounded.
     * 
     * @param chunk The current chunk that the block is being drawn to.
     * @param blockOffset Where the block needs to be drawn in the world.
     * @param texture The texture atlas containing the necessary textures to draw the block.
     */
    void LoadVBO(Chunk& chunk, const glm::vec3 blockOffset, const Texture& texture);
};
