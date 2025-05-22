#include "Renderer.hpp"

void Renderer::DrawChunk(std::shared_ptr<World> world, const Shader& shaderProgram, const Texture& texture, const Player& player)
{
	shaderProgram.UseProgram();
	texture.Bind();
	float x = player.GetPlayerPosition().x;
	float z = player.GetPlayerPosition().z;
	// Multiply CHUNK_XorZ by a factor to prevent chunk loading everytime a new chunk is entered :(
	if (((int)abs(x) % (CHUNK_X * world->getRenderDistance()) == 0) || ((int)abs(z) % (CHUNK_Z * world->getRenderDistance()) == 0))
	{
		world->UpdateChunks(player);
		world->GenerateChunks();
	}
	world->DrawChunks();
}

void Renderer::CheckCollisions(std::shared_ptr<Player> player, std::shared_ptr<World> world)
{
	glm::vec3 playerPos = player->GetPlayerPosition();
	glm::vec3 currentBlock = glm::vec3(floor(playerPos.x), floor(playerPos.y), floor(playerPos.z));

	// use direction vector instead
	BlockType north = world->FindBlock(currentBlock.x, currentBlock.y, currentBlock.z + 1);
	BlockType south = world->FindBlock(currentBlock.x, currentBlock.y, currentBlock.z - 1);
	BlockType east	= world->FindBlock(currentBlock.x + 1, currentBlock.y, currentBlock.z);
	BlockType west	= world->FindBlock(currentBlock.x - 1, currentBlock.y, currentBlock.z);
	BlockType up	= world->FindBlock(currentBlock.x, currentBlock.y + 1, currentBlock.z);
	BlockType down	= world->FindBlock(currentBlock.x, currentBlock.y - 1, currentBlock.z);

	
}
