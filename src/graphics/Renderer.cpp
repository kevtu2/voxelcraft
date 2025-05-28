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
	glm::vec3 aabbPos = aabb.GetMin();
	glm::vec3 playerPos = player->GetPlayerPosition();
	glm::vec3 currentBlock = glm::vec3(VMath::DivFloor(aabbPos.x, 1), VMath::DivFloor(aabbPos.y, 1), VMath::DivFloor(playerPos.z, 1));

	glm::vec3 direction;
	glm::vec3 velocity = player->GetVelocity();

	// Avoids division by zero when calculating normal vector
	if (glm::length(velocity))
		direction = glm::normalize(player->GetVelocity());
	else
		direction = glm::vec3(0.0f);

	glm::vec3 blockPos = aabbPos + glm::vec3(round(direction.x), round(direction.y), round(direction.z));
	BlockType block = world->FindBlock(VMath::DivFloor(blockPos.x, 1), VMath::DivFloor(blockPos.y, 1), VMath::DivFloor(blockPos.z, 1));

	std::cout << static_cast<int>(block) << std::endl;
	if (block != AIR && IsColliding(aabb, blockPos))
		DoCollisions(player, blockPos);

	/*std::cout << "Direction Pos: (" << round(direction.x) << ", " << round(direction.y) << ", " << round(direction.z) << ")" << std::endl;
	std::cout << "Block: (" << blockPos.x << ", " << blockPos.y << ", " << blockPos.z << ")" << std::endl;
	std::cout << "Player Pos: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;*/
	
}

bool Renderer::IsColliding(const AABB& box, const glm::vec3& block)
{
	// Note: blocks are 1 units in size
	bool collisionX = (box.max.x >= block.x) && (block.x + 1 >= box.min.x);
	bool collisionY = (box.max.y >= block.y) && (block.y + 1 >= box.min.y);
	bool collisionZ = (box.max.z >= block.z) && (block.z + 1 >= box.min.z);
	return collisionX && collisionY && collisionZ;
}

void Renderer::DoCollisions(std::shared_ptr<Player> player, const glm::vec3& block)
{
	AABB box = player->GetAABBCollision();
	glm::vec3 playerPos = player->GetPlayerPosition();
	glm::vec3 boxPos = box.GetMin();

	player->SetVelocity(glm::vec3(0.0f));
	
	std::cout << "Collided at: " << "(" << boxPos.x << ", " << boxPos.y << ", " << boxPos.z << ")" << std::endl;

	/*float dx = (boxPos.x + box.GetWidth()) - block.x;
	float dy = (boxPos.y + box.GetHeight()) - block.y;
	float dz = (boxPos.z + box.GetWidth()) - block.z;

	std::cout << "dx: " << dx << ", dy: " << dy << ", dz: " << dz << std::endl;

	float minOverlap = std::min({ dx, dy, dz });

	if (minOverlap == dx) player->ResetPosAfterCollision(playerPos - glm::vec3(dx, 0, 0));
	else if (minOverlap == dy) player->ResetPosAfterCollision(playerPos - glm::vec3(0, dy, 0));
	else player->ResetPosAfterCollision(playerPos - glm::vec3(0, 0, dz));*/
}
