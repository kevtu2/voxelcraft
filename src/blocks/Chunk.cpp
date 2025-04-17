#include "Chunk.hpp"


Chunk::Chunk()
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	position = glm::vec3(0, 0, 0);
	chunkMesh = new ChunkMesh();
	GenerateChunkVertexData();
}

Chunk::Chunk(int x, int y, int z)
	: position(glm::vec3(x, y, z))
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	chunkMesh = new ChunkMesh();
	GenerateChunkVertexData();
}


Chunk::~Chunk()
{
	glDeleteBuffers(1, &chunkVBO_ID);
	glDeleteBuffers(1, &chunkIBO_ID);
	glDeleteVertexArrays(1, &chunkVAO_ID);
	delete chunkMesh;
}


void Chunk::BufferData() const
{
	glBindVertexArray(chunkVAO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, chunkVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, chunkMesh->chunkVertexData.size() * sizeof(Vertex), chunkMesh->chunkVertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunkIBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunkMesh->chunkIndexData.size() * sizeof(unsigned int), chunkMesh->chunkIndexData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

}

void Chunk::DrawArrays() const
{
	glBindVertexArray(chunkVAO_ID);
	glDrawElements(GL_TRIANGLES, chunkMesh->chunkIndexData.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


BlockType Chunk::GetBlock(int x, int y, int z)
{
	if (y < surfaceY) return BlockType::STONE;
	if (y == surfaceY) return BlockType::GRASS;
	if (y > surfaceY) return BlockType::AIR;
}

void Chunk::GenerateChunkVertexData()
{
	for (size_t x = 0; x < CHUNK_X; ++x)
	{
		for (size_t y = 0; y < CHUNK_Y; ++y)
		{
			for (size_t z = 0; z < CHUNK_Z; ++z)
			{
				glm::vec3 worldPosition(x + (position.x * CHUNK_X), y, z + (position.z * CHUNK_Z));
				BlockType currentBlock = GetBlock(x, y, z);

				// Do not draw anything if the block is AIR
				if (currentBlock == BlockType::AIR) continue;

				// Check surrounding blocks and draw faces only if the adjacent block is transparent
				if (/*z == 0 ||*/ Block::IsTransparent(currentBlock))
					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, NORTH);

				if (/*z == CHUNK_Z - 1 ||*/ Block::IsTransparent(currentBlock))
					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, SOUTH);

				if (/*x == CHUNK_X - 1 ||*/ Block::IsTransparent(currentBlock))
					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, EAST);

				if (/*x == 0 ||*/ Block::IsTransparent(currentBlock))
					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, WEST);

				if (y == surfaceY || Block::IsTransparent(currentBlock))
					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, UP);

				if (y == 0 || Block::IsTransparent(currentBlock))
					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, DOWN);
			}
		}
	}
	BufferData();
}

