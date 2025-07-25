#include "Physics.hpp"

#include <iostream>

#include "Core/Utils.hpp"
#include "AABB.hpp"

float CalculateTime(float x, float y)
{
	if (y)
		return x / y;
	else
	{
		if (x > 0)
			return -std::numeric_limits<float>::infinity();
		else if (x < 0)
			return std::numeric_limits<float>::infinity();
		else
			return 0.0f;
	}
}

void Physics::CheckCollisions(std::shared_ptr<Player> player, std::shared_ptr<World> world, float deltaTime)
{
	// 3 iterations for 3 of the axes.
	for (int i = 0; i < 3; ++i)
	{
		AABB aabb = player->GetAABBCollision();

		glm::vec3 playerPos = player->GetPlayerPosition();
		glm::vec3 playerVel = player->GetVelocity();
		glm::vec3 aabbPos = aabb.min;

		// Current position
		glm::vec3 blockPos = glm::vec3(VMath::DivFloor(aabbPos.x, 1), VMath::DivFloor(aabbPos.y, 1), VMath::DivFloor(aabbPos.z, 1));

		glm::vec3 velocity = playerVel * deltaTime;

		std::vector<std::pair<float, glm::vec3>> collisionCandidates;

		// Broad phase
		Physics::BroadPhaseVolume box(aabb, velocity);
		glm::ivec3 minBlock = glm::floor(glm::vec3(box.x, box.y, box.z));
		glm::ivec3 maxBlock = glm::ceil(glm::vec3(box.x + box.l, box.y + box.h, box.z + box.w));

		for (int x = minBlock.x; x <= maxBlock.x; ++x)
		{
			for (int y = minBlock.y; y <= maxBlock.y; ++y)
			{
				for (int z = minBlock.z; z <= maxBlock.z; ++z)
				{
					BlockType block = world->FindBlock(x, y, z);
					if (block == AIR)
						continue;

					float collisionTime;
					glm::vec3 collisionNormal;
					CalculateCollisions(player, velocity, glm::vec3(x, y, z), collisionTime, collisionNormal);

					if (glm::all(glm::isnan(collisionNormal)))
						continue;

					std::pair<float, glm::vec3> candidate;
					candidate.first = collisionTime;
					candidate.second = collisionNormal;
					collisionCandidates.push_back(candidate);
				}
			}
		}

		if (collisionCandidates.empty())
			return;

		// Narrow phase
		float minTime = collisionCandidates.back().first;
		glm::vec3 minNormal = collisionCandidates.back().second;
		for (auto& candidate : collisionCandidates)
		{
			if (candidate.first < minTime)
			{
				minTime = candidate.first;
				minNormal = candidate.second;
			}
		}

		// Extra padding for collision
		minTime = glm::clamp(minTime - 0.001f, 0.0f, 1.0f);

		// Collide!
		glm::vec3 newVel = velocity;
		glm::vec3 pos = aabbPos;
		if (minNormal.x != 0)
		{
			newVel.x = 0;
			pos.x += velocity.x * minTime;
		}

		if (minNormal.y != 0)
		{
			newVel.y = 0;
			pos.y += velocity.y * minTime;
			player->SetIsGrounded(true);
		}

		if (minNormal.z != 0)
		{
			newVel.z = 0;
			pos.z += velocity.z * minTime;
		}

		player->SetVelocity(newVel / deltaTime);
		player->ResetPosAfterCollision(pos);
	}
}

void Physics::CalculateCollisions(std::shared_ptr<Player> player, const glm::vec3& velocity, const glm::vec3& block, float& outTime, glm::vec3& outNormal)
{
	AABB aabb = player->GetAABBCollision();
	glm::vec3 min = aabb.GetMin();
	glm::vec3 max = aabb.GetMax();

	// Entry and Exit times (distance / velocity)
	float xEntry = CalculateTime((velocity.x > 0) ? (block.x - max.x) : ((block.x + 1) - min.x), velocity.x);
	float xExit = CalculateTime((velocity.x > 0) ? ((block.x + 1) - min.x) : (block.x - max.x), velocity.x);

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
	if (xEntry < 0 && yEntry < 0 && zEntry < 0)
	{
		outTime = 1;
		outNormal = glm::vec3(NAN);
		return;
	}


	if (xEntry > 1 || yEntry > 1 || zEntry > 1)
	{
		outTime = 1;
		outNormal = glm::vec3(NAN);
		return;
	}

	float entryTime = std::max(xEntry, yEntry);
	entryTime = std::max(entryTime, zEntry);

	float exitTime = std::min(xExit, yExit);
	exitTime = std::min(exitTime, zExit);

	if (entryTime > exitTime)
	{
		outTime = 1;
		outNormal = glm::vec3(NAN);
		return;
	}

	// Calculate collision normals
	int xNormal = (entryTime == xEntry) ? (velocity.x > 0 ? -1 : 1) : 0;
	int yNormal = (entryTime == yEntry) ? (velocity.y > 0 ? -1 : 1) : 0;
	int zNormal = (entryTime == zEntry) ? (velocity.z > 0 ? -1 : 1) : 0;

	outTime = entryTime;
	outNormal = glm::vec3(xNormal, yNormal, zNormal);
}

void Physics::CalculateGravity(std::shared_ptr<Player> player, float deltaTime)
{
	glm::vec3 vel = player->GetVelocity();
	vel.y += (GRAVITY * deltaTime);
	vel.y = std::max(vel.y, TERMINAL_VEL);
	player->SetVelocity(vel);
}