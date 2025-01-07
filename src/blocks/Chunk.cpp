#include "Chunk.hpp"

void Chunk::AppendToVBO(float value)
{
	chunkVertexData.push_back(value);
}

void Chunk::AppentToIBO(unsigned int value)
{
	chunkIndexData.push_back(value);
}



void Chunk::PrintChunkData() const
{
	for (size_t i = 0; i < chunkVertexData.size(); ++i)
	{
		std::ostream& out = std::cout;
		if (i % 5 == 0)
			out << std::endl;
		out << chunkVertexData[i] << ", ";
	}
}
