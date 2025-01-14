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
	chunk.GenerateChunkData();
	//chunk.PrintChunkData();
	chunk.FilterVisibleFaces();
	chunk.BufferData();
	chunk.DrawArrays();
}
