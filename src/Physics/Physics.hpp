#pragma once
#include <glm/glm.hpp>

#include "World/Player.hpp"
#include "World/World.hpp"

#define GRAVITY -1000.f
#define TERMINAL_VEL -50.0f

namespace Physics
{

	struct BroadPhaseVolume
	{
		float x, y, z, l, w, h;

		BroadPhaseVolume(const AABB& aabb, const glm::vec3& playerVel)
		{
			glm::vec3 pos = aabb.GetMin();
			x = playerVel.x > 0 ? pos.x : pos.x + playerVel.x;
			y = playerVel.y > 0 ? pos.y : pos.y + playerVel.y;
			z = playerVel.z > 0 ? pos.z : pos.z + playerVel.z;

			l = aabb.GetWidth() + std::abs(playerVel.x);
			w = aabb.GetWidth() + std::abs(playerVel.z);
			h = aabb.GetHeight() + std::abs(playerVel.y);
		}
	};

	void CheckCollisions(std::shared_ptr<Player> player, std::shared_ptr<World> world, float deltaTime);
	void CalculateCollisions(std::shared_ptr<Player> player, const glm::vec3& adjustedVel, const glm::vec3& block, float& outTime, glm::vec3& outNormal);
	void CalculateGravity(std::shared_ptr<Player> player, float deltaTime);
};
