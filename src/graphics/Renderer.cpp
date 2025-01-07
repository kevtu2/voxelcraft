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
	Chunk chunk;
	Block grass(GRASS);
	BlockMesh::GenerateBlockFaceMesh(chunk, glm::vec3(0.0f, 0.0f, 0.0f), grass, texture, shaderProgram);
	if (!chunk.printed)
		chunk.PrintChunkData();
		
}
