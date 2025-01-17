#pragma once

#include "graphics/Vertex.hpp"

#include <vector>

class ChunkMesh
{
public:

	std::vector<Vertex> chunkVertexData;
	std::vector<unsigned int> chunkIndexData;
	unsigned int vertexCount = 0;

};