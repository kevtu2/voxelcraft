#pragma once

#include <glad/glad.h>
#include <vector>
#include <iostream>

#include "../graphics/Vertex.hpp"
#include "../blocks/BlockMesh.hpp"
#include "../blocks/Block.hpp"
#include "../blocks/ChunkMesh.hpp"

#define CHUNK_X 1
#define CHUNK_Y 1
#define CHUNK_Z 1


class Chunk
{
private:
	unsigned int chunkVBO_ID;
	unsigned int chunkVAO_ID;
	//unsigned int chunkIBO_ID;

	// Contains which blocks to generate
	// TODO: Implement terrain generator with this
	BlockType chunkData[CHUNK_X][CHUNK_Y][CHUNK_Z];

	unsigned int vertexCount = 0;
	
public:
	Chunk();
	~Chunk();

	ChunkMesh* chunkMesh;

	void BufferData() const;

	void DrawArrays() const;

	void GenerateChunkData();

};