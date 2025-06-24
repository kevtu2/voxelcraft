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
};