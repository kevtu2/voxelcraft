#pragma once

#include <glad/glad.h>
#include <vector>
#include <iostream>

#include "../graphics/Vertex.hpp"

#define CHUNK_SIZE_X 3
#define CHUNK_SIZE_Y 3
#define CHUNK_SIZE_Z 3

class Chunk
{
private:
	std::vector<Vertex> chunkVertexData;
	std::vector<unsigned int> chunkIndexData;
	unsigned int chunkVBO_ID;
	unsigned int chunkVAO_ID;
	//unsigned int chunkIBO_ID;
public:
	Chunk();
	~Chunk();

	void AppendToIBO(const float indices[]);
	void AddToChunkArray(Vertex vertex);

	void BufferData() const;
	
	std::vector<unsigned int> GetIndexData() const { return chunkIndexData; }

	void DrawArrays() const;

	void FilterVisibleFaces();

	std::vector<Vertex>& GetVertexDataArray() { return chunkVertexData; }

};