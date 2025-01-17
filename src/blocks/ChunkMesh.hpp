#pragma once

#include "graphics/Vertex.hpp"

#include <vector>
#include <iostream>

class ChunkMesh
{
public:

	std::vector<Vertex> chunkVertexData;
	std::vector<unsigned int> chunkIndexData;
	unsigned int vertexCount = 0;

	void PrintChunkVertex() const;
	void PrintChunkIndices() const;
};