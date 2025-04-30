#pragma once
#include <memory>
#include <set>
#include <glm/glm.hpp>
#include <unordered_map>
#include <unordered_set>

#include "Chunk.hpp"
#include "../graphics/Camera.hpp"
#include "../blocks/Vec2Hashes.hpp"

class World
{
private:
	int renderDistance;

	// Chunk data
	std::unique_ptr<Chunk> spawnChunk;
	std::unordered_map<glm::vec2, std::unique_ptr<Chunk>, Vec2Hasher, Vec2Equals> activeChunks;
	std::unordered_set<glm::vec2, Vec2Hasher, Vec2Equals> dirtyChunks;


public:
	World();
	~World();

	void UpdateChunks(const Camera& player);
	void GenerateChunks();
	void DrawChunks();

	void setRenderDistance(unsigned int renderDistance);
	unsigned int getRenderDistance() const { return renderDistance; }

};