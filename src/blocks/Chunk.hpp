#pragma once

#include <glad/glad.h>
#include <vector>
#include <iostream>

#include "../graphics/Vertex.hpp"
#include "../blocks/BlockMesh.hpp"
#include "../blocks/Block.hpp"

#define CHUNK_X 32
#define CHUNK_Y 32
#define CHUNK_Z 32


class Chunk
{
private:
	std::vector<Vertex> chunkVertexData;
	std::vector<unsigned int> chunkIndexData;
	unsigned int chunkVBO_ID;
	unsigned int chunkVAO_ID;
	//unsigned int chunkIBO_ID;

	// Contains which blocks to generate
	// TODO: Implement terrain generator with this
	int chunkData[CHUNK_X][CHUNK_Y][CHUNK_Z];
	Block blocks[CHUNK_X][CHUNK_Y][CHUNK_Z];

	
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

	void GenerateChunkData();

};