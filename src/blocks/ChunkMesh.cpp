#include "ChunkMesh.hpp"

void ChunkMesh::PrintChunkVertex() const
{
	for (Vertex vertex : chunkVertexData)
	{
		std::cout 
			<< vertex.xPos << ", " 
			<< vertex.yPos << ", " 
			<< vertex.zPos << ", " 
			<< vertex.xUV << ", " 
			<< vertex.yUV << std::endl;
	}
}

void ChunkMesh::PrintChunkIndices() const
{
	for (unsigned int index : chunkIndexData)
	{
		std::cout << index << std::endl;
	}
}
