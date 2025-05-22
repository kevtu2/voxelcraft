#pragma once
#include <glad/glad.h>

#include "Shader.hpp"
#include "../blocks/Chunk.hpp"
#include "../blocks/Texture.hpp"
#include "../blocks/BlockGeneration.hpp"
#include "../graphics/Player.hpp"
#include "../blocks/World.hpp"
#include "../graphics/AABB.hpp"

namespace Renderer
{
	void DrawChunk(std::shared_ptr<World> world, const Shader& shaderProgram, const Texture& texture, const Player& player);

	void CheckCollisions(std::shared_ptr<Player> player, std::shared_ptr<World> world);
	bool CalculateCollisions(const AABB& box, const glm::vec3& block);
};