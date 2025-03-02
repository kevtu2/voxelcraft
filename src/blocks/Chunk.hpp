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

#define surfaceY 100


class Chunk
{
private:
	// Chunk world position
	glm::vec3 position;

	unsigned int chunkVBO_ID;
	unsigned int chunkVAO_ID;
	unsigned int chunkIBO_ID;

	// Contains which blocks to generate
	// TODO: Implement terrain generator with this
	// BlockType chunkData[CHUNK_X][CHUNK_Y][CHUNK_Z];

	unsigned int vertexCount = 0;

public:
	Chunk();
	Chunk(int x, int y, int z);

	~Chunk();

	ChunkMesh* chunkMesh;

	void BufferData() const;

	void DrawArrays() const;

	void GenerateChunkVertexData();
	
	// Terrain generator
	BlockType GetBlock(int x, int y, int z);
	
	glm::vec3 GetWorldPosition() const { return position; }
};