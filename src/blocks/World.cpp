#include "World.hpp"
#include "../blocks/World.hpp"


World::World()
	: renderDistance(6)
{
	perlinNoise = FastNoiseLite();
	perlinNoise.SetSeed(1337);
	perlinNoise.SetFrequency(0.01f);
	perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	// Generate new world chunks
	for (int x = -renderDistance; x < renderDistance; ++x)
	{
		for (int z = -renderDistance; z < renderDistance; ++z)
		{
			glm::vec2 chunkPos = glm::vec2(x, z);
			std::unique_ptr<Chunk> currentChunk = std::make_unique<Chunk>(x, 0, z);
			currentChunk->GenerateBlockData(this);
			activeChunks.emplace(chunkPos, std::move(currentChunk));
		}
	}
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

				if (activeChunks.contains(chunkPos + glm::vec2(-1, 0)))
				{
					activeChunks.at(chunkPos + glm::vec2(-1, 0))->chunkReady = false;
				}

				if (activeChunks.contains(chunkPos + glm::vec2(1, 0)))
				{
					activeChunks.at(chunkPos + glm::vec2(1, 0))->chunkReady = false;
				}

				if (activeChunks.contains(chunkPos + glm::vec2(0, -1)))
				{
					activeChunks.at(chunkPos + glm::vec2(0, -1))->chunkReady = false;
				}

				if (activeChunks.contains(chunkPos + glm::vec2(0, 1)))
				{
					activeChunks.at(chunkPos + glm::vec2(0, 1))->chunkReady = false;
				}
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
}

void World::GenerateChunks()
{
	for (auto& pair : activeChunks)
	{
		if (!pair.second->chunkReady)
		{
			pair.second->GenerateChunkMesh(this);
		}
	}
}

BlockType World::FindBlock(int x, int y, int z) const
{
	int chunkX = DivFloor(x, CHUNK_X);
	int chunkZ = DivFloor(z, CHUNK_Z);

	glm::vec2 chunkWorldPos = glm::vec2(chunkX, chunkZ);
	if (activeChunks.contains(chunkWorldPos))
	{
		return activeChunks.at(chunkWorldPos)->GetBlock(x, y, z);
	}
	return BlockType::STONE; // Prevent it from generating the face if chunk doesn't exist yet.
}

float World::GetNoise(int x, int y)
{
	float xFloat = static_cast<float>(x);
	float yFloat = static_cast<float>(y);
	return perlinNoise.GetNoise(xFloat, yFloat);
}

void World::DrawChunks()
{
	for (auto& pair : activeChunks)
	{
		pair.second->DrawArrays();
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

int World::DivFloor(int x, int y) const
{
	int res = x / y;
	int rem = x % y;
	int corr = (rem != 0 && ((rem < 0) != (y < 0)));
	return res - corr;
}
