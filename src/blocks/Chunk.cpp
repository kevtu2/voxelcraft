#include "Chunk.hpp"

void Chunk::AppendToChunk(float value)
{
	chunkData.push_back(value);
}

void Chunk::PrintChunkData() const
{
	for (size_t i = 0; i < chunkData.size(); ++i)
	{
		std::ostream& out = std::cout;
		if (i % 5 == 0)
			out << "," << std::endl;
		out << chunkData[i] << ", ";
	}
}
