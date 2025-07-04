#pragma once

#include <glad/glad.h>
#include <vector>
#include <array>
#include <memory>
#include <FastNoiseLite.hpp>

#include "Blocks/Block.hpp"
#include "World/ChunkMesh.hpp"

#define CHUNK_X 16
#define CHUNK_Y 384
#define CHUNK_Z 16
#define CHUNK_BLOCK_COUNT CHUNK_X * CHUNK_Y * CHUNK_Z
#define surfaceY 100
#define PERLIN_OCTAVES 8
#define PERLIN_GRID_SIZE 400

class World;

class Chunk
{
private:
	// Chunk world position
	glm::ivec3 position;

	unsigned int chunkVBO_ID;
	unsigned int chunkVAO_ID;
	unsigned int chunkIBO_ID;

	unsigned int vertexCount = 0;

	// Use to identify which blocks are contained in the chunk
	std::array<unsigned char, CHUNK_BLOCK_COUNT> blocks;
	
	FastNoiseLite perlinNoise;

public:
	Chunk();
	Chunk(int x, int y, int z, FastNoiseLite noise);

	~Chunk();

	std::unique_ptr<ChunkMesh> chunkMesh;
	
	Chunk(Chunk&& o) noexcept;
	Chunk& operator=(Chunk&& o) noexcept;

	Chunk(const Chunk&) = delete;
	Chunk& operator=(const Chunk&) = delete;

	void BufferData() const;

	void DrawArrays() const;

	//void GenerateChunkVertexData();
	
	glm::ivec3 GetWorldPosition() const { return position; }

	BlockType GetBlock(int x, int y, int z) const;

	void GenerateBlockData();
	void GenerateChunkMesh(World* world);

	bool IsReady() const { return chunkReady; }

	bool chunkReady = false;

};