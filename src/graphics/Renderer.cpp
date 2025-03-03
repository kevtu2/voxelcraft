#include "Renderer.hpp"

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
