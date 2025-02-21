#pragma once
#include <memory>

#include "Chunk.hpp"

class World
{
private:
	unsigned int renderDistance;

	// Chunk data
	std::unique_ptr<Chunk> currentChunk;


public:
	World();
	~World();

	void setRenderDistance(unsigned int distance);
	unsigned int getRenderDistance() const { return renderDistance; }

};