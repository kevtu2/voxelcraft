#include "Renderer.hpp"

#include "World/Chunk.hpp"
#include "Blocks/BlockGeneration.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Renderer::UpdateWorldChunks(std::atomic_ref<GameState> atomicGameState, std::atomic<World*>& atomicWorld, std::shared_ptr<Texture> texture, std::shared_ptr<Player> player)
{
    // ~60 Hz updates
    const std::chrono::milliseconds updateInterval(16);
	float prevX = player->GetPlayerPosition().x;
	float prevZ = player->GetPlayerPosition().z;

    while (!atomicGameState.load().quitGame)
    {
        auto start = std::chrono::steady_clock::now();

        World* world = atomicWorld.load();

        if (!world)
        {
            std::this_thread::sleep_for(updateInterval);
            continue;
        }

        texture->Bind();
        float x = player->GetPlayerPosition().x;
        float z = player->GetPlayerPosition().z;

		float xDiff = std::abs(x - prevX);
		float zDiff = std::abs(z - prevZ);
        if (xDiff > (CHUNK_X) ||
            zDiff > (CHUNK_Z))
        {
            prevX = x;
            prevZ = z;

            world->UpdateChunks(*(player.get()));
            world->GenerateChunks();
        }

        // Sleep for remaining time to maintain steady update rate
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed < updateInterval)
        {
            std::this_thread::sleep_for(updateInterval - elapsed);
        }
    }
}