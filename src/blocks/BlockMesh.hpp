#pragma once
#include "Texture.hpp"
#include "Chunk.hpp"
#include "../graphics/Shader.hpp"
#include "../graphics/Vertex.hpp"
#include "../blocks/Block.hpp"
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

#define CHUNK_X 32
#define CHUNK_Y 32
#define CHUNK_Z 32


enum Face {
    F_TOP,
    F_SIDE,
    F_BOT
};

// Adapted from jdh
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
     /**
     * @brief Generates vertex data depending on the block currently bounded.
     * 
     * @param chunk The current chunk that the block is being drawn to.
     * @param blockOffset Where the block needs to be drawn in the world.
     * @param texture The texture atlas containing the necessary textures to draw the block.
     */
    static void LoadVBO(Block(&blocks)[CHUNK_X][CHUNK_Y][CHUNK_Z], BlockType type, const glm::vec3 blockOffset);
};
