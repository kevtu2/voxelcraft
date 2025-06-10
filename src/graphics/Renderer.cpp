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
	glm::vec3 playerPos = player->GetPlayerPosition();
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
				isColliding |= (block != AIR && IsColliding(aabb, glm::vec3(x, y, z)));
				glm::vec3 diff = aabbPos - glm::vec3(x, y, z);
				if (isColliding)
					DoCollisions(player, glm::vec3(x, y, z));
			}
		}
	}
}

bool Renderer::IsIntersecting(const AABB& box, const glm::vec3& block)
{
	// Note: blocks are 1 units in size
	bool collisionX = (box.max.x >= block.x) && (block.x + 1 >= box.min.x);
	bool collisionY = (box.max.y >= block.y) && (block.y + 1 >= box.min.y);
	bool collisionZ = (box.max.z >= block.z) && (block.z + 1 >= box.min.z);
	return collisionX && collisionY && collisionZ;
}

void Renderer::CalculateCollisions(std::shared_ptr<Player> player, const glm::vec3& block, float& outTime, glm::vec3& outNormal)
{
	AABB aabb = player->GetAABBCollision();
	glm::vec3 velocity = player->GetVelocity();
	glm::vec3 min = aabb.GetMin();
	glm::vec3 max = aabb.GetMax();

	// Entry and Exit times (distance / velocity)
	float xEntry = CalculateTime((velocity.x > 0) ? (block.x - max.x) : ((block.x + 1) - min.x), velocity.x);
	float xExit  = CalculateTime((velocity.x > 0) ? ((block.x + 1) - min.x) : (block.x - max.x), velocity.x);

	float yEntry = CalculateTime((velocity.y > 0) ? (block.y - max.y) : ((block.y + 1) - min.y), velocity.y);
	float yExit = CalculateTime((velocity.y > 0) ? ((block.y + 1) - min.y) : (block.y - max.y), velocity.y);

	float zEntry = CalculateTime((velocity.z > 0) ? (block.z - max.z) : ((block.z + 1) - min.z), velocity.z);
	float zExit = CalculateTime((velocity.z > 0) ? ((block.z + 1) - min.z) : (block.z - max.z), velocity.z);

	/* No collision conditions:
	* This occurs when the entry distance is greater than where the player will be in the next tick. In other
	* words, the block is too far to collide with the player in the very next tick. (entryTime > velocity)
	* We will "normalize" wrt velocity and get that:
	* if entry time > 1, (i.e, entryTime > velocity), then the block is too far away, therefore no collision.
	* if entry time < 0, represents a past collision which will already be handled.
	* Source: Obiwac's collision physics video (https://www.youtube.com/watch?v=fWkbIOna6RA)
	*/
	if (xEntry < 0 and yEntry < 0 and zEntry < 0)
	{
		outTime = 1;
		outNormal = glm::vec3(NAN);
		return;
	}
		

	if (xEntry > 1 or yEntry > 1 or zEntry > 1) 
	{
		outTime = 1;
		outNormal = glm::vec3(NAN);
		return;
	}
		
	float entryTime = std::max(xEntry, yEntry, zEntry);
	float exitTime = std::min(xExit, yExit, zExit);

	if (entryTime > exitTime) 
	{
		outTime = 1;
		outNormal = glm::vec3(NAN);
		return;
	}

	// Calculate collision normals
	int xNormal = [0, velocity.x > 0 ? -1 : 1][entryTime = xEntry];
	int yNormal = [0, velocity.y > 0 ? -1 : 1][entryTime = yEntry];
	int zNormal = [0, velocity.z > 0 ? -1 : 1][entryTime = zEntry];

	outTime = entryTime;
	outNormal = glm::vec3(xNormal, yNormal, zNormal);
}

static float CalculateTime(float x, float y)
{
	if (y)
		return x / y;
	else
		return -(x > 0) * std::numeric_limits<float>::max();
}

static bool IsVec3Invalid(const glm::vec3& v)
{
	return std::isnan(v.x) || std::isnan(v.y) || std::isnan(v.z);
}