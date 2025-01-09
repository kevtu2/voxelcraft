#include "Chunk.hpp"

Chunk::Chunk()
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
}

Chunk::~Chunk()
{
	glDeleteBuffers(1, &chunkVBO_ID);
	glDeleteBuffers(1, &chunkIBO_ID);
	glDeleteVertexArrays(1, &chunkVAO_ID);
}

void Chunk::AppendToVBO(float value)
{
	chunkVertexData.push_back(value);
}

void Chunk::AppendToIBO(unsigned int value)
{
	chunkIndexData.push_back(value);
}

void Chunk::BufferData() const
{
	glBindVertexArray(chunkVAO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, chunkVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, chunkVertexData.size() * sizeof(float), &chunkVertexData[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunkIBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunkIndexData.size() * sizeof(unsigned int), &chunkIndexData[0], GL_STATIC_DRAW);
}

void Chunk::PrintChunkData() const
{
	for (size_t i = 0; i < chunkVertexData.size(); ++i)
	{
		std::ostream& out = std::cout;
		if (i % 5 == 0)
			out << std::endl;
		out << chunkVertexData[i] << ", ";
	}
}
