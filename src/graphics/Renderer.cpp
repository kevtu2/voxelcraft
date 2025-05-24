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
	AABB aabb = player->GetAABBCollision();
	glm::vec3 playerPos = aabb.GetPosition();
	glm::vec3 currentBlock = glm::vec3(VMath::DivFloor(playerPos.x, 1), VMath::DivFloor(playerPos.y, 1), VMath::DivFloor(playerPos.z, 1));
	
	std::cout << "Player Pos: " << player->GetPlayerPosition().x << ", " << player->GetPlayerPosition().y << ", " << player->GetPlayerPosition().z << std::endl;

	// use direction vector instead
	BlockType north = world->FindBlock(currentBlock.x, currentBlock.y, currentBlock.z + 1);
	if (CalculateCollisions(aabb, currentBlock + glm::vec3(0, 0, 1)) && north != AIR)
		DoCollisions(player, currentBlock + glm::vec3(0, 0, 1));

	BlockType south = world->FindBlock(currentBlock.x, currentBlock.y, currentBlock.z - 1);
	if (CalculateCollisions(aabb, currentBlock + glm::vec3(0, 0, -1)) && south != AIR)
		DoCollisions(player, currentBlock + glm::vec3(0, 0, -1));

	BlockType east	= world->FindBlock(currentBlock.x + 1, currentBlock.y, currentBlock.z);
	if (CalculateCollisions(aabb, currentBlock + glm::vec3(1, 0, 0)) && east != AIR)
		DoCollisions(player, currentBlock + glm::vec3(1, 0, 0));

	BlockType west	= world->FindBlock(currentBlock.x - 1, currentBlock.y, currentBlock.z);
	if (CalculateCollisions(aabb, currentBlock + glm::vec3(-1, 0, 0)) && west != AIR)
		DoCollisions(player, currentBlock + glm::vec3(-1, 0, 0));

	BlockType up	= world->FindBlock(currentBlock.x, currentBlock.y + 1, currentBlock.z);
	if (CalculateCollisions(aabb, currentBlock + glm::vec3(0, 1, 0)) && up != AIR)
		DoCollisions(player, currentBlock + glm::vec3(0, 1, 0));

	BlockType down	= world->FindBlock(currentBlock.x, currentBlock.y - 1, currentBlock.z);
	if (CalculateCollisions(aabb, currentBlock + glm::vec3(0, -1, 0)) && down != AIR)
		DoCollisions(player, currentBlock + glm::vec3(0, -1, 0));

}

bool Renderer::CalculateCollisions(const AABB& box, const glm::vec3& block)
{
	// Note: blocks are 1 units in size
	glm::vec3 boxPos = box.GetPosition();
	bool collisionX = (boxPos.x + box.GetWidth()  >= block.x) && (block.x + 1 >= boxPos.x);
	bool collisionY = (boxPos.y + box.GetHeight() >= block.y) && (block.y + 1 >= boxPos.y);
	bool collisionZ = (boxPos.z + box.GetWidth()  >= block.z) && (block.z + 1 >= boxPos.z);
	return collisionX && collisionY && collisionZ;
}

void Renderer::DoCollisions(std::shared_ptr<Player> player, const glm::vec3& block)
{
	std::cout << "Collided with block at: (" << block.x << ", " << block.y << ", " << block.z << ")" << std::endl;
}
