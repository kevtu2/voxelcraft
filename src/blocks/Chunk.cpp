#include "Chunk.hpp"

Chunk::Chunk()
{
	glGenBuffers(1, &chunkVBO_ID);
	//glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);

	chunkMesh = new ChunkMesh();

	// TODO: Replace this with a terrain generator
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
	delete chunkMesh;
}


void Chunk::BufferData() const
{
	glBindVertexArray(chunkVAO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, chunkVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, chunkMesh->chunkVertexData.size() * sizeof(Vertex), chunkMesh->chunkVertexData.data(), GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunkIBO_ID);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunkMesh->chunkIndexData.size() * sizeof(unsigned int), chunkMesh->chunkIndexData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

}

void Chunk::DrawArrays() const
{
	glDrawArrays(GL_TRIANGLES, 0, chunkMesh->chunkVertexData.size());
	//glDrawElements(GL_TRIANGLES, chunkMesh->chunkIndexData.size(), GL_UNSIGNED_INT, 0);
}


void Chunk::GenerateChunkData()
{	
	bool shouldDraw = true;
	for (size_t x = 0; x < CHUNK_X; ++x)
	{
		for (size_t y = 0; y < CHUNK_Y; ++y)
		{
			for (size_t z = 0; z < CHUNK_Z; ++z)
			{	
				// Boundary blocks
				if (x == 0 || y == 0 || z == 0 || x == CHUNK_X - 1 || y == CHUNK_Y - 1 || z == CHUNK_Z - 1)
				{
					// For now, I'm gonna just render the redundant faces for these boundary blocks
					// TODO: Fix logic for boundary blocks
					BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), WEST);
					BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), DOWN);
					BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), NORTH);
					BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), EAST);
					BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), UP);
					BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), SOUTH);
					continue;
				}
				// Check surrounding blocks for transparent faces
				if (Block::IsTransparent(chunkData[x - 1][y][z])) BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), WEST);
				if (Block::IsTransparent(chunkData[x][y - 1][z])) BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), DOWN);
				if (Block::IsTransparent(chunkData[x][y][z - 1])) BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), NORTH);
				if (Block::IsTransparent(chunkData[x + 1][y][z])) BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), EAST);
				if (Block::IsTransparent(chunkData[x][y + 1][z])) BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), UP);
				if (Block::IsTransparent(chunkData[x][y][z + 1])) BlockMesh::AddFace(chunkMesh, chunkData[x][y][z], glm::vec3(x, y, z), SOUTH);
				// BlockMesh::LoadVBO(chunkRawVertexData, chunkData[x][y][z], glm::vec3(x, y, z));
			}
		}
	}
	/*chunkMesh->PrintChunkIndices();
	chunkMesh->PrintChunkVertex();*/
}

