#pragma once
#include "../graphics/Vertex.hpp"
#include "../blocks/Block.hpp"
#include "../blocks/ChunkMesh.hpp"

#include <glm/glm.hpp>
#include <vector>


namespace BlockGeneration
{
    // Cube data adapted from jdah's weekend minecraft repository
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

    static constexpr unsigned int CUBE_UNIQUE_INDICES[] = { 1, 0, 5, 2 };


    // SIZE_OF_TEXTURE will just be multiplied by an offset to choose whichever texture that specific face uses.
    /*static constexpr float CUBE_UV_COORDS[] =
    {
        0,               0,
        SIZE_OF_TEXTURE, 0,
        SIZE_OF_TEXTURE, SIZE_OF_TEXTURE,
        0,               SIZE_OF_TEXTURE,
    };*/

    static constexpr float CUBE_UV_COORDS[] =
    {
        SIZE_OF_TEXTURE, 0,
        0,               0,
        0,               SIZE_OF_TEXTURE,
        SIZE_OF_TEXTURE, SIZE_OF_TEXTURE
    };


    static constexpr unsigned int CUBE_UV_INDICES[] = { 1, 0, 3, 1, 3, 2 };

    static constexpr unsigned int FACE_INDICES[] = { 1, 0, 3, 1, 3, 2 };

     void GenerateFace(std::unique_ptr<ChunkMesh> chunkMesh, BlockType type, const glm::vec3 blockOffset, Face face);

};


