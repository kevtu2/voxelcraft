#pragma once
#include <memory>
#include <set>
#include <glm/glm.hpp>
#include <unordered_map>

#include "Chunk.hpp"
#include "../graphics/Camera.hpp"

class World
{
	// Define hasher for glm::vec2 used for unordered_map (activeChunks)
	struct Vec2Hasher
	{
		std::size_t operator()(const glm::vec2& c) const
		{
			// XOR hashes of x and z in chunkPos
			return hash<int>()(c.x) ^ (hash<int>()(c.y) << 1);
		}
	};

private:
	unsigned int renderDistance;

	// Chunk data
	std::unique_ptr<Chunk> spawnChunk;
	std::unordered_map<glm::vec2, Chunk, Vec2Hasher> activeChunks;
	std::set<glm::vec2> dirtyChunks;


public:
	World();
	~World();

	void UpdateChunks(const Camera& player);

	void setRenderDistance(unsigned int renderDistance);
	unsigned int getRenderDistance() const { return renderDistance; }

};