#include "Renderer.hpp"

#include "World/Chunk.hpp"
#include "Blocks/BlockGeneration.hpp"

void Renderer::DrawChunk(std::shared_ptr<World> world, std::shared_ptr<Texture> texture, std::shared_ptr<Player> player)
{
	while (true)
	{
		texture->Bind();
		float x = player->GetPlayerPosition().x;
		float z = player->GetPlayerPosition().z;

		// Multiply CHUNK_XorZ by a factor to prevent chunk loading everytime a new chunk is entered :(
		if (((int)abs(x) % (CHUNK_X * world->getRenderDistance()) == 0) || ((int)abs(z) % (CHUNK_Z * world->getRenderDistance()) == 0))
		{
			world->UpdateChunks(*(player.get()));
			world->GenerateChunks();
		}
		world->DrawChunks();
	}
}