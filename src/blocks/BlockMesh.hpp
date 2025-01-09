#pragma once
#include "Block.hpp"
#include "Texture.hpp"
#include "Chunk.hpp"
#include "../graphics/Shader.hpp"
#include <glm/glm.hpp>
#include <vector>


static constexpr float sizeOfTexture = 0.0625f;

static constexpr float CUBE_VERTICES[] =
{
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f
};

static constexpr unsigned int CUBE_INDICES[] =
{
    // Front face
    4, 5, 6,  4, 6, 7,
    // Back face
    0, 1, 2,  0, 2, 3,
    // Left face
    0, 3, 7,  0, 7, 4,
    // Right face
    1, 2, 6,  1, 6, 5,
    // Top face
    3, 2, 6,  3, 6, 7,
    // Bottom face
    0, 1, 5,  0, 5, 4
};


// sizeOfTexture will just be multiplied by an offset to choose whichever texture that specific face uses.
static constexpr float CUBE_UV_COORDS[] =
{
    0.0f,          0.0f,           // Bottom-left
    sizeOfTexture, 0.0f,           // Bottom-right
    sizeOfTexture, sizeOfTexture,  // Top-right
    0.0f,          sizeOfTexture   // Top-left
};

class BlockMesh
{
public:
    static void GenerateBlock(Chunk& chunk, const glm::vec3 blockOffset, const Block& block, const Texture& texture, const Shader& shaderProgram);
};
