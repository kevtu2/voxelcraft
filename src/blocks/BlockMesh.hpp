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
    1, 0, 3, 1, 3, 2, // north (-z)
    4, 5, 6, 4, 6, 7, // south (+z)
    5, 1, 2, 5, 2, 6, // east (+x)
    0, 4, 7, 0, 7, 3, // west (-x)
    2, 3, 7, 2, 7, 6, // top (+y)
    5, 4, 0, 5, 0, 1, // bottom (-y)
};


// sizeOfTexture will just be multiplied by an offset to choose whichever texture that specific face uses.
static constexpr float CUBE_UV_COORDS[] =
{
    sizeOfTexture, 0.0f,
    0.0f,          0.0f,
    0.0f,          sizeOfTexture,
    sizeOfTexture, sizeOfTexture
};

class BlockMesh
{
public:
    static void GenerateBlock(Chunk& chunk, const glm::vec3 blockOffset, const Block& block, const Texture& texture, const Shader& shaderProgram);
};
