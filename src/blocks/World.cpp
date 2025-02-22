#include "World.hpp"

World::World()
	: renderDistance(12)
{
	currentChunk = new Chunk(0, 0, 0);
}

World::~World()
{
	delete currentChunk;
}

// TODO: Change this so that player camera is not contained inside of application.

void World::UpdateChunks(const Camera& player)
{
	// Calculate current reference Chunk X-Z position.
	int playerChunkPosX = (int) (player.GetCameraPosition() / CHUNK_X);
	int playerChunkPosZ = (int) (player.GetCameraPosition() / CHUNK_Z);

	dirtyChunks.clear();

	// Add all the previous coordinates to remove
	for (auto& chunk : activeChunks)
	{
		dirtyChunks.insert(chunk.first);
	}

	// Determine which chunks needs to be added & removed
	for (int x = playerChunkPosX - renderDistance; x <= playerChunkPosX + renderDistance; ++x)
	{
		for (int z = playerChunkPosZ - renderDistance; z <= playerChunkPosZ + renderDistance; ++z)
		{
			glm::vec2 chunkPos = glm::vec2(x, z);

			// This generates chunks that aren't generated already.
			if (!activeChunks.contains(chunkPos))
			{
				Chunk currentChunk = new Chunk(x, 0, z);
				std::pair<glm::vec2, Chunk> chunkPair = std::pair(chunkPos, currentChunk);
				activeChunks.insert(chunkPair);
			}
			// This prevents visible chunks that are already generated from deletion
			else if (activeChunks.contains(chunkPos))
			{
				dirtyChunks.erase(chunkPos);
			}
		}
	}
}

void World::setRenderDistance(unsigned int renderDistance)
{
	if (renderDistance > 32) 
	{
		this->renderDistance = 32;
	}
	this->renderDistance = renderDistance;
}