#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <set>
#include <atomic>
#include <mutex>
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
	std::shared_ptr<Chunk> spawnChunk;
	FastNoiseLite perlinNoise;
	std::mutex updateRunnableChunksMutex;

public:
	World();
	~World();

	void UpdateChunks(const Player& player);
	void GenerateChunks();
	void DrawChunks();
	FastNoiseLite& GetNoiseInstance() { return perlinNoise; }
	BlockType FindBlock(int x, int y, int z) const;

	std::atomic<bool> worldReady = false;
	std::atomic<bool> chunksReady = false;

	std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>, Vec2Hasher, Vec2Equals> activeChunks;
	std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>, Vec2Hasher, Vec2Equals> runnableChunks;
	std::unordered_set<glm::ivec2, Vec2Hasher, Vec2Equals> dirtyChunks;
	std::mutex deleteChunksMutex;


	inline void SetRenderDistance(unsigned int value)
	{
		{
			if (value > 32)
			{
				renderDistance = 32;
			}
			else if (value < 5)
			{
				renderDistance = 5;
			}
			else
			{
				renderDistance = value;
			}
		}
	}
	unsigned int GetRenderDistance() const { return renderDistance; }
};