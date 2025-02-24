#include "World.hpp"

World::World()
	: renderDistance(12)
{
	spawnChunk = std::unique_ptr<Chunk>(new Chunk(0, 0, 0));
	activeChunks.emplace(glm::vec2(0, 0), std::move(spawnChunk));

}

World::~World()
{
	
}

// TODO: Change this so that player camera is not contained inside of application.
void World::UpdateChunks(const Camera& player)
{
	// Calculate current reference Chunk X-Z position.
	int playerChunkPosX = (int) (player.GetCameraPosition().x / CHUNK_X);
	int playerChunkPosZ = (int) (player.GetCameraPosition().z / CHUNK_Z);

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
				std::unique_ptr<Chunk> currentChunk = std::make_unique<Chunk>(x, 0, z);
				activeChunks.emplace(chunkPos, std::move(currentChunk));
			}
			// This prevents visible chunks that are already generated from deletion
			else if (activeChunks.contains(chunkPos))
			{
				dirtyChunks.erase(chunkPos);
			}
		}
	}
}

void World::DrawChunks()
{
	for (auto& pair : activeChunks)
	{
		pair.second->GenerateChunkVertexData();
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