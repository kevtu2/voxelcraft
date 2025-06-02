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
	glm::vec3 aabbPos = aabb.min;

	glm::vec3 blockPos = glm::vec3(VMath::DivFloor(aabbPos.x, 1), VMath::DivFloor(aabbPos.y, 1), VMath::DivFloor(aabbPos.z, 1));

	//std::cout << "Current block: (" << blockPos.x << ", " << blockPos.y << ", " << blockPos.z << ")" << std::endl;
	bool isColliding = false;
	for (int x = blockPos.x - 1; x <= blockPos.x + 1; ++x)
	{
		for (int y = blockPos.y - 1; y <= blockPos.y + 3; ++y)
		{
			for (int z = blockPos.z - 1; z <= blockPos.z + 1; ++z)
			{
				BlockType block = world->FindBlock(x, y, z);
				//std::cout << "Block type: " << static_cast<int>(block) << " at: (" << x << ", " << y << ", " << z << ")" << std::endl;
				isColliding |= (block != AIR && IsColliding(aabb, glm::vec3(x, y, z)));
				if (isColliding)
					DoCollisions(player, blockPos);
			}
		}
	}
	player->SetIsColliding(isColliding);
	std::cout << "isColliding: " << isColliding << std::endl;
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
	glm::vec3 aabbMin = box.min;
	glm::vec3 playerPos = player->GetPlayerPosition();
	std::cout << "Collided with: " << "(" << block.x << ", " << block.y << ", " << block.z << ")" << std::endl;
	std::cout << "______________________" << std::endl;

	glm::vec3 velocity = glm::vec3(0.0f);
	player->SetVelocity(velocity);

	float dx = (aabbMin.x + box.GetWidth()) - block.x;
	float dy = (aabbMin.y + box.GetHeight()) - block.y;
	float dz = (aabbMin.z + box.GetWidth()) - block.z;

	std::cout << "dx: " << dx << ", dy: " << dy << ", dz: " << dz << std::endl;

	float minOverlap = std::min({ dx, dy, dz });

	if (minOverlap == dx) player->ResetPosAfterCollision(playerPos - glm::vec3(dx, 0, 0));
	else if (minOverlap == dy) player->ResetPosAfterCollision(playerPos - glm::vec3(0, dy, 0));
	else player->ResetPosAfterCollision(playerPos - glm::vec3(0, 0, dz));
}
