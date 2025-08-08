#include "Renderer.hpp"

#include "World/Chunk.hpp"
#include "Blocks/BlockGeneration.hpp"
#include <iostream>
#include <chrono>

void Renderer::DrawChunk(std::atomic<std::shared_ptr<World>>& worldAtomic, std::shared_ptr<Texture> texture, std::shared_ptr<Player> player)
{
    // ~60 Hz updates
    const std::chrono::milliseconds updateInterval(16);

    while (true)
    {
        auto start = std::chrono::steady_clock::now();

        std::shared_ptr<World> world = worldAtomic.load();
        if (!world)
        {
            std::this_thread::sleep_for(updateInterval);
            continue;
        }

        texture->Bind();
        float x = player->GetPlayerPosition().x;
        float z = player->GetPlayerPosition().z;

        if (((int)abs(x) % (CHUNK_X * world->getRenderDistance()) == 0) ||
            ((int)abs(z) % (CHUNK_Z * world->getRenderDistance()) == 0))
        {
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