#pragma once
#include <glad/glad.h>
#include <utility>
#include <vector>

#include "World/Player.hpp"
#include "World/World.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

#include "Physics/AABB.hpp"

namespace Renderer
{
	void DrawChunk(std::shared_ptr<World> world, const Shader& shaderProgram, const Texture& texture, const Player& player);

	void CheckCollisions(std::shared_ptr<Player> player, std::shared_ptr<World> world, float deltaTime);
	bool IsIntersecting(const AABB& box, const glm::vec3& block);
	void CalculateCollisions(std::shared_ptr<Player> player, const glm::vec3& adjustedVel, const glm::vec3& block, float& outTime, glm::vec3& outNormal);
};