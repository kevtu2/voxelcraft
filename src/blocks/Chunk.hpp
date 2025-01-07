#pragma once
#include <vector>
#include <iostream>

class Chunk
{
private:
	std::vector<float> chunkVertexData;
	std::vector<unsigned int> chunkIndexData;
public:
	bool printed = false;
	void AppendToVBO(float value);
	void AppentToIBO(unsigned int value);
	void PrintChunkData() const;
};