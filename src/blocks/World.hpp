#pragma once
#include <memory>
#include <set>

#include "Chunk.hpp"
#include "../graphics/Camera.hpp"

class World
{
private:
	unsigned int renderDistance;

	// Chunk data
	std::unique_ptr<Chunk> spawnChunk;
	std::unordered_map<glm::vec2, Chunk> activeChunks;
	std::set<glm::vec2> dirtyChunks;


public:
	World();
	~World();

	void UpdateChunks(const Camera& player);

	void setRenderDistance(unsigned int renderDistance);
	unsigned int getRenderDistance() const { return renderDistance; }

};