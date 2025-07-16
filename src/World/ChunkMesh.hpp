#pragma once

#include "Graphics/Vertex.hpp"

#include <vector>

class ChunkMesh
{
public:

	std::vector<Vertex> chunkVertexData;
	std::vector<unsigned int> chunkIndexData;
	unsigned int vertexCount = 0;

	void Clear();
	void PrintChunkVertex() const;
	void PrintChunkIndices() const;
};
