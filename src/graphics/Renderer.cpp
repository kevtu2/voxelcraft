#include "Renderer.hpp"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shaderProgram) 
{
	shaderProgram.UseProgram();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

void Renderer::DrawChunk(const Shader& shaderProgram, const Texture& texture)
{
	shaderProgram.UseProgram();
	texture.Bind();
	Chunk chunk;
	BlockMesh grass(DIRT);

	for (size_t x = 0; x < CHUNK_SIZE_X; ++x)
	{
		for (size_t y = 0; y < CHUNK_SIZE_Y; ++y)
		{
			for (size_t z = 0; z < CHUNK_SIZE_Z; ++z)
			{
				grass.LoadVBO(chunk, glm::vec3(x, y, z), texture);
			}
		}
	}

	//chunk.PrintChunkData();
	//chunk.FilterVisibleFaces();
	chunk.BufferData();
	chunk.DrawArrays();
}
