#pragma once

#include <glad/glad.h>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "../graphics/Vertex.hpp"
#include "../blocks/BlockGeneration.hpp"
#include "../blocks/Block.hpp"
#include "../blocks/ChunkMesh.hpp"
#include "../graphics/PerlinNoise.hpp"

#define CHUNK_X 2
#define CHUNK_Y 384
#define CHUNK_Z 2
#define CHUNK_BLOCK_COUNT CHUNK_X * CHUNK_Y * CHUNK_Z
#define surfaceY 100
#define PERLIN_OCTAVES 8
#define PERLIN_GRID_SIZE 400

class World;

class Chunk
{
private:
	// Chunk world position
	glm::vec3 position;

	unsigned int chunkVBO_ID;
	unsigned int chunkVAO_ID;
	unsigned int chunkIBO_ID;

	unsigned int vertexCount = 0;

	// Use to identify which blocks are contained in the chunk
	unsigned char blocks[CHUNK_BLOCK_COUNT];

public:
	Chunk();
	Chunk(int x, int y, int z);

	~Chunk();

	ChunkMesh* chunkMesh;

	void BufferData() const;

	void DrawArrays() const;

	//void GenerateChunkVertexData();
	
	glm::vec3 GetWorldPosition() const { return position; }

	BlockType GetBlock(int x, int y, int z) const;

	void GenerateBlockData();
	void GenerateChunkMesh(World* world) const;
};