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
	std::vector<Vertex> chunkRawVertexData;
	// The idea is that once we determine which face is hidden from the player,
	// We can remove it from rendering, but we still have its original data so
	// when it is visible (when breaking a block, etc) it can be added back to be rendered.
	std::vector<Vertex> chunkVertexData;

	std::vector<unsigned int> chunkIndexData;
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

	void AppendToIBO(const float indices[]);
	void AddToChunkArray(Vertex vertex);

	void BufferData() const;
	
	std::vector<unsigned int> GetIndexData() const { return chunkIndexData; }

	void DrawArrays() const;

	void FilterVisibleFaces();

	std::vector<Vertex>& GetVertexDataArray() { return chunkVertexData; }

	void GenerateChunkData();

};