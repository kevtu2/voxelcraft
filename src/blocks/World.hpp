#pragma once
#include <memory>
#include <set>
#include <glm/glm.hpp>
#include <unordered_map>
#include <unordered_set>

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
			return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
		}
	};

	struct Vec2Equals
	{
		bool operator()(const glm::vec2& lhs, const glm::vec2& rhs) const
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
	};

private:
	unsigned int renderDistance;

	// Chunk data
	std::unique_ptr<Chunk> spawnChunk;
	std::unordered_map<glm::vec2, std::unique_ptr<Chunk>, Vec2Hasher, Vec2Equals> activeChunks;
	std::unordered_set<glm::vec2, Vec2Hasher, Vec2Equals> dirtyChunks;


public:
	World();
	~World();

	void UpdateChunks(const Camera& player);
	void DrawChunks();

	void setRenderDistance(unsigned int renderDistance);
	unsigned int getRenderDistance() const { return renderDistance; }

};