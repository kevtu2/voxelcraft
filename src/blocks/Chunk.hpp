#pragma once
#include "glad/glad.h"

#include <vector>
#include <iostream>

class Chunk
{
private:
	std::vector<float> chunkVertexData;
	std::vector<unsigned int> chunkIndexData;
	unsigned int chunkVBO_ID;
	unsigned int chunkVAO_ID;
public:
	Chunk();
	~Chunk();

	void AppendToVBO(float value);
	void AppendToIBO(unsigned int value);

	void BufferData() const;

	void PrintChunkData() const;
	
	std::vector<unsigned int> GetIndexData() const {return chunkIndexData;}

	void DrawArrays() const;
};