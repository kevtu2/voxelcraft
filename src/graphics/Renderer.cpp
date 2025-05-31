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
	glm::vec3 aabbPosMax = aabb.GetMax();
	glm::vec3 playerPos = player->GetPlayerPosition();
	glm::vec3 currentBlock = glm::vec3(VMath::DivFloor(aabbPos.x, 1), VMath::DivFloor(aabbPos.y, 1), VMath::DivFloor(playerPos.z, 1));

	/*std::cout << "aabb min: (" << aabbPos.x << ", " << aabbPos.y << ", " << aabbPos.z << ")" << std::endl;
	std::cout << "aabb max: (" << aabbPosMax.x << ", " << aabbPosMax.y << ", " << aabbPosMax.z << ")" << std::endl;*/
	glm::vec3 direction;
	glm::vec3 velocity = player->GetVelocity();

	// Avoids division by zero when calculating normal vector
	if (glm::length(velocity))
		direction = glm::normalize(player->GetVelocity());
	else
		direction = glm::vec3(0.0f);

	glm::vec3 blockPos = 
		glm::vec3(round(aabbPos.x), round(aabbPos.y), round(aabbPos.z)) 
		+ glm::vec3(round(direction.x), round(direction.y), round(direction.z));
	blockPos = glm::vec3(VMath::DivFloor(blockPos.x, 1), VMath::DivFloor(blockPos.y, 1), VMath::DivFloor(blockPos.z, 1));

	BlockType block = world->FindBlock(blockPos.x, blockPos.y, blockPos.z);

	if (block != AIR && IsColliding(aabb, blockPos))
		DoCollisions(player, blockPos);

	/*std::cout << "Box pos: (" << aabb.pos.x << ", " << aabb.pos.y << ", " << aabb.pos.z << ")" << std::endl;

	std::cout << "Box min: (" << aabb.min.x << ", " << aabb.min.y << ", " << aabb.min.z << ")" << std::endl;
	
	std::cout << "Box max: (" << aabb.max.x << ", " << aabb.max.y << ", " << aabb.max.z << ")" << std::endl;*/

	//std::cout << static_cast<int>(block) << std::endl;

	/*std::cout << "Direction Pos: (" << round(direction.x) << ", " << round(direction.y) << ", " << round(direction.z) << ")" << std::endl;*/
	/*std::cout << "Block: (" << VMath::DivFloor(blockPos.x, 1) << ", " << VMath::DivFloor(blockPos.y, 1) << ", " << VMath::DivFloor(blockPos.z, 1) << ")" << std::endl;
	std::cout << "Player Pos: (" << round(aabbPos.x) << ", " << round(aabbPos.y) << ", " << round(aabbPos.z) << ")" << std::endl;*/
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

	std::cout << "Collided at: " << "(" << block.x << ", " << block.y << ", " << block.z << ")" << std::endl;

	/*float dx = (boxPos.x + box.GetWidth()) - block.x;
	float dy = (boxPos.y + box.GetHeight()) - block.y;
	float dz = (boxPos.z + box.GetWidth()) - block.z;

	std::cout << "dx: " << dx << ", dy: " << dy << ", dz: " << dz << std::endl;

	float minOverlap = std::min({ dx, dy, dz });

	if (minOverlap == dx) player->ResetPosAfterCollision(playerPos - glm::vec3(dx, 0, 0));
	else if (minOverlap == dy) player->ResetPosAfterCollision(playerPos - glm::vec3(0, dy, 0));
	else player->ResetPosAfterCollision(playerPos - glm::vec3(0, 0, dz));*/
}
