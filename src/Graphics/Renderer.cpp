#include "Renderer.hpp"

#include "World/Chunk.hpp"
#include "Blocks/BlockGeneration.hpp"
#include <iostream>
#include <chrono>

void Renderer::DrawChunk(std::atomic_ref<GameState> atomicGameState, std::atomic<std::shared_ptr<World>>& atomicWorld, std::shared_ptr<Texture> texture, std::shared_ptr<Player> player)
{
    // ~60 Hz updates
    const std::chrono::milliseconds updateInterval(16);

    while (!atomicGameState.load().quitGame)
    {
        auto start = std::chrono::steady_clock::now();

        std::shared_ptr<World> world = atomicWorld.load();

        if (!world)
        {
            std::this_thread::sleep_for(updateInterval);
            continue;
        }

        texture->Bind();
        float x = player->GetPlayerPosition().x;
        float z = player->GetPlayerPosition().z;

        world->UpdateChunks(*(player.get()));
        world->GenerateChunks();

        // Sleep for remaining time to maintain steady update rate
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed < updateInterval)
        {
            std::this_thread::sleep_for(updateInterval - elapsed);
        }
    }
}