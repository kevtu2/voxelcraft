#include "Renderer.hpp"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shaderProgram) 
{
	shaderProgram.UseProgram();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

void Renderer::DrawChunk(World* world, const Shader& shaderProgram, const Texture& texture, const Camera& player)
{
	shaderProgram.UseProgram();
	texture.Bind();
	float x = player.GetCameraPosition().x;
	float z = player.GetCameraPosition().z;
	// Multiply CHUNK_XorZ by a factor to prevent chunk loading everytime a new chunk is entered :(
	if (((int)abs(x) % CHUNK_X == 0) || ((int)abs(z) % CHUNK_Z == 0))
	{
		world->UpdateChunks(player);
	}
	world->DrawChunks();
}
