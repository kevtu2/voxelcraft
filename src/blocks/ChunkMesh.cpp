#include "ChunkMesh.hpp"

void ChunkMesh::PrintChunkVertex() const
{
	for (const Vertex& vertex : chunkVertexData)
	{
		std::cout 
			<< vertex.x << ", " 
			<< vertex.y << ", " 
			<< vertex.z << ", " 
			<< vertex.u << ", " 
			<< vertex.v << std::endl;
	}
	std::cout << "Number of vertices: " << chunkVertexData.size();
}

void ChunkMesh::PrintChunkIndices() const
{
	for (unsigned int index : chunkIndexData)
	{
		std::cout << index << std::endl;
	}
}
