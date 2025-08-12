#include "World.hpp"

#include "Core/Utils.hpp"

World::World()
	: renderDistance(12)
{
	perlinNoise = FastNoiseLite();
	perlinNoise.SetSeed(rand());
	perlinNoise.SetFrequency(0.01f);
	perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	for (int x = -renderDistance; x < renderDistance; ++x)
	{
		for (int z = -renderDistance; z < renderDistance; ++z)
		{
			glm::ivec2 chunkPos = glm::ivec2(x, z);
			std::unique_ptr<Chunk> currentChunk = std::make_unique<Chunk>(x, 0, z, perlinNoise);
			activeChunks.emplace(chunkPos, std::move(currentChunk));
		}
	}
	GenerateChunks();
	runnableChunks = activeChunks; // Copy active chunks to runnable chunks
	worldReady.store(true);
}

World::~World()
{

}

void World::UpdateChunks(const Player& player)
{
	std::lock_guard<std::mutex> lock(chunkMutex);
	int playerChunkPosX = (int)(player.GetPlayerPosition().x / CHUNK_X);
	int playerChunkPosZ = (int)(player.GetPlayerPosition().z / CHUNK_Z);

	dirtyChunks.clear();

	for (auto& chunk : activeChunks)
	{
		dirtyChunks.insert(chunk.first);
	}

	// Determine which chunks needs to be added & removed
	for (int x = playerChunkPosX - renderDistance; x <= playerChunkPosX + renderDistance; ++x)
	{
		for (int z = playerChunkPosZ - renderDistance; z <= playerChunkPosZ + renderDistance; ++z)
		{
			glm::ivec2 chunkPos = glm::ivec2(x, z);

			// This generates chunks that aren't generated already.
			if (!activeChunks.contains(chunkPos))
			{
				std::unique_ptr<Chunk> currentChunk = std::make_unique<Chunk>(x, 0, z, perlinNoise);
				activeChunks.emplace(chunkPos, std::move(currentChunk));

				// Older chunks need to remesh if they are adjacent to the new chunk
				if (activeChunks.contains(chunkPos + glm::ivec2(-1, 0)))
					activeChunks.at(chunkPos + glm::ivec2(-1, 0))->chunkReady = false;

				if (activeChunks.contains(chunkPos + glm::ivec2(1, 0)))
					activeChunks.at(chunkPos + glm::ivec2(1, 0))->chunkReady = false;

				if (activeChunks.contains(chunkPos + glm::ivec2(0, -1)))
					activeChunks.at(chunkPos + glm::ivec2(0, -1))->chunkReady = false;

				if (activeChunks.contains(chunkPos + glm::ivec2(0, 1)))
					activeChunks.at(chunkPos + glm::ivec2(0, 1))->chunkReady = false;

			}
			// This prevents visible chunks that are already generated from deletion
			else if (activeChunks.contains(chunkPos))
			{
				dirtyChunks.erase(chunkPos);
			}
		}
	}

	// Delete chunks outside render distance
	for (auto& chunkKey : dirtyChunks)
	{
		activeChunks.erase(chunkKey);
	}
	dirtyChunks.clear();
}

void World::GenerateChunks()
{
	std::lock_guard<std::mutex> lock(chunkMutex);
	for (auto& pair : activeChunks)
	{
		if (!pair.second->chunkReady.load())
		{
			pair.second->GenerateChunkMesh(this);
		}
	}
	if (!worldReady) // Initial world generation
		worldReady.store(true);

	chunksReady.store(true);
}

BlockType World::FindBlock(int x, int y, int z) const
{
	int chunkX = VMath::DivFloor(x, CHUNK_X);
	int chunkZ = VMath::DivFloor(z, CHUNK_Z);

	glm::vec2 chunkWorldPos = glm::ivec2(chunkX, chunkZ);
	if (activeChunks.contains(chunkWorldPos))
	{
		return activeChunks.at(chunkWorldPos)->GetBlock(x, y, z);
	}
	return BlockType::BOUNDARY; // Prevent it from generating the face if chunk doesn't exist yet.
}

void World::DrawChunks()
{
	for (auto& pair : runnableChunks)
	{
		if (pair.second->chunkReady.load())
		{
			pair.second->BufferData();
			pair.second->DrawArrays();
		}
	}
	std::lock_guard<std::mutex> lock(chunkMutex);
	runnableChunks = activeChunks;
}

