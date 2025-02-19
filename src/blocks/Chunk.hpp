#pragma once

#include <glad/glad.h>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "../graphics/Vertex.hpp"
#include "../blocks/BlockGeneration.hpp"
#include "../blocks/Block.hpp"
#include "../blocks/ChunkMesh.hpp"

#define CHUNK_X 16
#define CHUNK_Y 384
#define CHUNK_Z 16


class Chunk
{
private:
	unsigned int chunkVBO_ID;
	unsigned int chunkVAO_ID;
	unsigned int chunkIBO_ID;

	// Contains which blocks to generate
	// TODO: Implement terrain generator with this
	BlockType chunkData[CHUNK_X][CHUNK_Y][CHUNK_Z];

	unsigned int vertexCount = 0;

	const int surfaceY = 100;
	
public:
	Chunk();
	~Chunk();

	ChunkMesh* chunkMesh;

	void BufferData() const;

	void DrawArrays() const;

	void GenerateChunkVertexData();
	
	// Terrain generator
	BlockType GetBlock(int x, int y, int z);
	

};