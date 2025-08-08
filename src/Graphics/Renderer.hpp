#pragma once
#include <glad/glad.h>
#include <utility>
#include <vector>
#include <atomic>

#include "World/Player.hpp"
#include "World/World.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"
#include "Core/GameState.hpp"

#include "Physics/AABB.hpp"

namespace Renderer
{
	void DrawChunk(std::atomic_ref<GameState> atomicGameState, std::atomic<std::shared_ptr<World>>& atomicWorld, std::shared_ptr<Texture> texture, std::shared_ptr<Player> player);
};