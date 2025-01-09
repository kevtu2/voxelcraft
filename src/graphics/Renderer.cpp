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
	Block grass(GRASS);
	for (size_t x = 0; x < 2; ++x)
	{
		for (size_t y = 0; y < 2; ++y)
		{
			for (size_t z = 0; z < 2; ++z)
			{
				BlockMesh::GenerateBlock(chunk, glm::vec3(x,y,z), grass, texture, shaderProgram);
			}
		}
	}
	chunk.PrintChunkData();
	chunk.BufferData();
	auto IBO = chunk.GetIndexData();
	glDrawElements(GL_TRIANGLES, IBO.size(), GL_UNSIGNED_INT, 0);
}
