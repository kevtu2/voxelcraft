#include "Chunk.hpp"
#include "World.hpp"


Chunk::Chunk()
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	position = glm::vec3(0, 0, 0);
	chunkMesh = new ChunkMesh();
	blocks.reserve(CHUNK_BLOCK_COUNT);
	GenerateBlockData();
}

Chunk::Chunk(int x, int y, int z)
	: position(glm::vec3(x * CHUNK_X, y, z * CHUNK_Z))
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	chunkMesh = new ChunkMesh();
	blocks.reserve(CHUNK_BLOCK_COUNT);
	GenerateBlockData();
}


Chunk::~Chunk()
{
	glDeleteBuffers(1, &chunkVBO_ID);
	glDeleteBuffers(1, &chunkIBO_ID);
	glDeleteVertexArrays(1, &chunkVAO_ID);
	delete chunkMesh;
}


void Chunk::BufferData() const
{
	glBindVertexArray(chunkVAO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, chunkVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, chunkMesh->chunkVertexData.size() * sizeof(Vertex), chunkMesh->chunkVertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunkIBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunkMesh->chunkIndexData.size() * sizeof(unsigned int), chunkMesh->chunkIndexData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Chunk::DrawArrays() const
{
	glBindVertexArray(chunkVAO_ID);
	glDrawElements(GL_TRIANGLES, chunkMesh->chunkIndexData.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//void Chunk::GenerateChunkVertexData()
//{
//	for (size_t x = 0; x < CHUNK_X; ++x)
//	{
//		for (size_t y = 0; y < CHUNK_Y; ++y)
//		{
//			for (size_t z = 0; z < CHUNK_Z; ++z)
//			{
//				int yValue = rand();
//				if (yValue > surfaceY) yValue = surfaceY;
//				if (yValue < 0.f) yValue = 0.f;
//
//				glm::vec3 worldPosition(position.x + x, rand(), position.z + z);
//				BlockType currentBlock = GetBlock(x, y, z);
//				BlockType bpx = getBlock()
//
//				// Do not draw anything if the block is AIR
//				if (currentBlock == BlockType::AIR) continue;
//
//			
//
//				// Check surrounding blocks and draw faces only if the adjacent block is transparent
//				if (/*z == 0 ||*/ Block::IsTransparent(currentBlock))
//					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, NORTH);
//
//				if (/*z == CHUNK_Z - 1 ||*/ Block::IsTransparent(currentBlock))
//					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, SOUTH);
//
//				if (/*x == CHUNK_X - 1 ||*/ Block::IsTransparent(currentBlock))
//					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, EAST);
//
//				if (/*x == 0 ||*/ Block::IsTransparent(currentBlock))
//					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, WEST);
//
//				if (y == surfaceY || Block::IsTransparent(currentBlock))
//					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, UP);
//
//				if (y == 0 || Block::IsTransparent(currentBlock))
//					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, DOWN);
//			}
//		}
//	}
//	BufferData();
//}

void Chunk::GenerateBlockData()
{
	for (size_t x = 0; x < CHUNK_X; ++x)
	{
		for (size_t y = 0; y < CHUNK_Y; ++y)
		{
			for (size_t z = 0; z < CHUNK_Z; ++z)
			{
				if (y < surfaceY)  blocks.push_back(static_cast<std::byte>(BlockType::STONE));
				else if (y == surfaceY) blocks.push_back(static_cast<std::byte>(BlockType::GRASS));
				else if (y > 100)  blocks.push_back(static_cast<std::byte>(BlockType::AIR));
			}
		}
	}
}

void Chunk::GenerateChunkMesh(World* world) const
{
	for (size_t x = 0; x < CHUNK_X; ++x)
	{
		for (size_t y = 0; y < CHUNK_Y; ++y)
		{
			for (size_t z = 0; z < CHUNK_Z; ++z)
			{
				BlockType currentBlock = GetBlock(x, y, z);
				glm::vec3 worldPosition(position.x + x, y, position.z + z);

				// Chunk boundary checks
				if (x == 0)
				{
					BlockType block = world->FindBlockFromChunk(glm::vec2(x - 1, z), CHUNK_X, y, z);
					if (Block::IsTransparent(block)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, WEST);
				}
				else
				{
					BlockType bnx = GetBlock(x - 1, y, z);
					if (Block::IsTransparent(bnx)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, WEST);
				}

				if (x == CHUNK_X - 1)
				{
					BlockType block = world->FindBlockFromChunk(glm::vec2(x + 1, z), 0, y, z);
					if (Block::IsTransparent(block)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, EAST);
				}
				else
				{
					BlockType bpx = GetBlock(x + 1, y, z);
					if (Block::IsTransparent(bpx)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, EAST);
				}

				if (z == 0)
				{
					BlockType block = world->FindBlockFromChunk(glm::vec2(x, z - 1), x, y, CHUNK_Z);
					if (Block::IsTransparent(block)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, NORTH);
				}
				else
				{
					BlockType npz = GetBlock(x, y, z - 1);
					if (Block::IsTransparent(npz)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, NORTH);
				}

				if (z == CHUNK_Z - 1)
				{
					BlockType block = world->FindBlockFromChunk(glm::vec2(x, z + 1), x, y, 0);
					if (Block::IsTransparent(block)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, SOUTH);
				}
				else
				{
					BlockType bpz = GetBlock(x, y, z + 1);
					if (Block::IsTransparent(bpz)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, SOUTH);
				}

				// Other checks
				if (y == CHUNK_Y - 1)
				{
					BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, UP);
				}
				else
				{
					BlockType bpy = GetBlock(x, y + 1, z);
					if (Block::IsTransparent(bpy)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, UP);
				}

				if (y == 0)
				{
					continue;
				}
				else
				{
					BlockType bny = GetBlock(x, y - 1, z);
					if (Block::IsTransparent(bny)) BlockGeneration::GenerateFace(chunkMesh, currentBlock, worldPosition, DOWN);
				}
			}
		}
	}
	BufferData();
}

BlockType Chunk::GetBlock(int x, int y, int z) const
{
	unsigned int index = x + (y * CHUNK_Y) + (z * CHUNK_Y * CHUNK_Z);
	std::byte blockID = blocks.at(index);
	return Block::GetBlockTypeFromID(blockID);
}

/*float yValue = 0;
float freq = 1;
float amp = 1;
for (int i = 0; i < PERLIN_OCTAVES; ++i)
{
	yValue += pNoise.SamplePerlin(x * freq / PERLIN_GRID_SIZE, z * freq / PERLIN_GRID_SIZE);
	freq *= 2;
	amp /= 2;
}
if (yValue > CHUNK_Y) yValue = CHUNK_Y;
if (yValue < 0.f) yValue = 0.f;*/