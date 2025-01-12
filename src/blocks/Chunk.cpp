#include "Chunk.hpp"

Chunk::Chunk()
{
	glGenBuffers(1, &chunkVBO_ID);
	//glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	chunkVertexData.reserve(CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
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
