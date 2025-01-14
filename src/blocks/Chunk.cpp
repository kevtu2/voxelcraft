#include "Chunk.hpp"

Chunk::Chunk()
{
	glGenBuffers(1, &chunkVBO_ID);
	//glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	chunkVertexData.reserve(CHUNK_X * CHUNK_Y * CHUNK_Z);

	// Top grass layer
	for (int x = 0; x < CHUNK_X; ++x)
	{
		for (int z = 0; z < CHUNK_Z; ++z)
		{
			chunkData[x][CHUNK_Y - 1][z] = BlockType::GRASS;
		}
	}

	// Lower dirt layers
	for (int x = 0; x < CHUNK_X; ++x)
	{
		for (int y = 0; y < CHUNK_Y - 1; ++y)
		{
			for (int z = 0; z < CHUNK_Z; ++z)
			{
				chunkData[x][y][z] = BlockType::DIRT;
			}
		}
	}
}

Chunk::~Chunk()
{
	glDeleteBuffers(1, &chunkVBO_ID);
	//glDeleteBuffers(1, &chunkIBO_ID);
	glDeleteVertexArrays(1, &chunkVAO_ID);
}


void Chunk::AppendToIBO(const float indices[])
{
	chunkIndexData.insert(chunkIndexData.end(), &indices[0], &indices[sizeof(indices)/sizeof(float)]);
}

void Chunk::AddToChunkArray(Vertex vertex)
{
	chunkVertexData.push_back(vertex);
}

void Chunk::BufferData() const
{
	glBindVertexArray(chunkVAO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, chunkVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, chunkVertexData.size() * sizeof(Vertex), chunkVertexData.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunkIBO_ID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunkIndexData.size() * sizeof(unsigned int), &chunkIndexData[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

}

void Chunk::DrawArrays() const
{
	glDrawArrays(GL_TRIANGLES, 0, chunkVertexData.size());
}

void Chunk::FilterVisibleFaces()
{
	bool shouldDraw = true;
	for (size_t x = 0; x < CHUNK_X; ++x)
	{
		for (size_t y = 0; y < CHUNK_Y; ++y)
		{
			for (size_t z = 0; z < CHUNK_Z; ++z)
			{
				std::vector<Vertex> blockVertices = blocks[x][y][z].GetBlockVertices();
				// If the current block is air, it shouldn't be drawn
				if (blocks[x][y][z].IsTransparent()) // Currently does not draw water, leaves, etc.
					shouldDraw = false;

				// Boundary blocks should be drawn
				else if (x == 0 || y == 0 || z == 0 || x == CHUNK_X - 1 || y == CHUNK_Y - 1 || z == CHUNK_Z - 1)
					shouldDraw = true;
				// Check surrounding blocks if they are transparent
				else
				{
					shouldDraw = 
						blocks[x - 1][y][z].IsTransparent() ||
						blocks[x][y - 1][z].IsTransparent() ||
						blocks[x][y][z - 1].IsTransparent() ||
						blocks[x + 1][y][z].IsTransparent() ||
						blocks[x][y + 1][z].IsTransparent() ||
						blocks[x][y][z + 1].IsTransparent();
				}

				if (shouldDraw)
				{
					for (Vertex vertex : blockVertices)
					{
						chunkVertexData.push_back(vertex);
					}
				}
			}
		}
	}
}

void Chunk::GenerateChunkData()
{
	for (size_t x = 0; x < CHUNK_X; ++x)
	{
		for (size_t y = 0; y < CHUNK_Y; ++y)
		{
			for (size_t z = 0; z < CHUNK_Z; ++z)
			{
				BlockMesh::LoadVBO(blocks, static_cast<BlockType>(chunkData[x][y][z]), glm::vec3(x, y, z));
			}
		}
	}
}
