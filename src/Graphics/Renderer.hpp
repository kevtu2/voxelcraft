#pragma once
#include <glad/glad.h>
#include <utility>
#include <vector>
#include <atomic>

#include "World/Player.hpp"
#include "World/World.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

#include "Physics/AABB.hpp"

namespace Renderer
{
	void DrawChunk(std::atomic<bool>& quitApp, std::atomic<std::shared_ptr<World>>& worldAtomic, std::shared_ptr<Texture> texture, std::shared_ptr<Player> player);
};