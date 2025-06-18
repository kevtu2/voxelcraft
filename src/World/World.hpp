#pragma once
#include <memory>
#include <set>
#include <glm/glm.hpp>
#include <unordered_map>
#include <unordered_set>
#include <FastNoiseLite.hpp>

#include "Chunk.hpp"
#include "Player.hpp"


class World
{
	// Define hasher for glm::vec2 used for unordered_map (activeChunks)
	struct Vec2Hasher
	{
		std::size_t operator()(const glm::ivec2& c) const
		{
			// XOR hashes of x and z in chunkPos
			return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
		}
	};

	struct Vec2Equals
	{
		bool operator()(const glm::ivec2& lhs, const glm::ivec2& rhs) const
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
	};
private:
	int renderDistance;

	// Chunk data
	std::unique_ptr<Chunk> spawnChunk;
	std::unordered_map<glm::ivec2, std::unique_ptr<Chunk>, Vec2Hasher, Vec2Equals> activeChunks;
	std::unordered_set<glm::ivec2, Vec2Hasher, Vec2Equals> dirtyChunks;
	
	FastNoiseLite perlinNoise;

public:
	World();
	~World();

	void UpdateChunks(const Player& player);
	void GenerateChunks();
	void DrawChunks();
	BlockType FindBlock(int x, int y, int z) const;

	void setRenderDistance(unsigned int renderDistance);
	unsigned int getRenderDistance() const { return renderDistance; }
};