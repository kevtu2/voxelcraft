#pragma once
#include <vector>
#include <iostream>

class Chunk
{
private:
	std::vector<float> chunkData;
public:
	bool printed = false;
	void AppendToChunk(float value);
	void PrintChunkData() const;
};