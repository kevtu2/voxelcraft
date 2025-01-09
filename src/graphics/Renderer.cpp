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

	BlockMesh::GenerateBlock(chunk, glm::vec3(0.f,0.f,0.f), grass, texture, shaderProgram);

	chunk.PrintChunkData();
	chunk.BufferData();
	auto IBO = chunk.GetIndexData();
	glDrawElements(GL_TRIANGLES, IBO.size(), GL_UNSIGNED_INT, 0);
}
