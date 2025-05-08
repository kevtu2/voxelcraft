#include "Chunk.hpp"
#include "World.hpp"


Chunk::Chunk()
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	position = glm::vec3(0, 0, 0);
	chunkMesh = std::make_unique<ChunkMesh>();
	GenerateBlockData();
}

Chunk::Chunk(int x, int y, int z)
	: position(glm::vec3(x, y, z))
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	chunkMesh = std::make_unique<ChunkMesh>();
	GenerateBlockData();
}


Chunk::~Chunk()
{
	glDeleteBuffers(1, &chunkVBO_ID);
	glDeleteBuffers(1, &chunkIBO_ID);
	glDeleteVertexArrays(1, &chunkVAO_ID);
}


Chunk::Chunk(Chunk&& o) noexcept
	: position(std::move(o.position)),
	chunkVBO_ID(o.chunkVBO_ID),
	chunkVAO_ID(o.chunkVAO_ID),
	chunkIBO_ID(o.chunkIBO_ID),
	vertexCount(o.vertexCount),
	blocks(std::move(o.blocks)),
	chunkMesh(std::move(o.chunkMesh))
{
	o.chunkVBO_ID = 0;
	o.chunkVAO_ID = 0;
	o.chunkIBO_ID = 0;
	o.vertexCount = 0;
}

Chunk& Chunk::operator=(Chunk&& o) noexcept
{
	if (this == &o) return *this;
	else
	{
		position = std::move(o.position);
		chunkVBO_ID = o.chunkVBO_ID;
		chunkVAO_ID = o.chunkVAO_ID;
		chunkIBO_ID = o.chunkIBO_ID;
		vertexCount = o.vertexCount;
		blocks = std::move(o.blocks);
		chunkMesh = std::move(o.chunkMesh);
		
		o.chunkVBO_ID = 0;
		o.chunkVAO_ID = 0;
		o.chunkIBO_ID = 0;
		o.vertexCount = 0;
	}
	return *this;
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


void Chunk::GenerateBlockData()
{
	for (size_t x = 0; x < CHUNK_X; ++x)
	{
		for (size_t y = 0; y < CHUNK_Y; ++y)
		{
			for (size_t z = 0; z < CHUNK_Z; ++z)
			{
				unsigned int index = x + (y * CHUNK_X) + (z * CHUNK_Y * CHUNK_X);
				if (y < surfaceY)  blocks[index] = static_cast<unsigned char>(BlockType::STONE);
				else if (y == surfaceY)  blocks[index] = static_cast<unsigned char>(BlockType::GRASS);
				else if (y > 100)   blocks[index] = static_cast<unsigned char>(BlockType::AIR);
			}
		}
	}
}

void Chunk::GenerateChunkMesh(World* world)
{
	chunkMesh->Clear();
	for (int x = 0; x < CHUNK_X; ++x)
	{
		for (int y = 0; y < CHUNK_Y; ++y)
		{
			for (int z = 0; z < CHUNK_Z; ++z)
			{
				glm::vec3 blockWorldPos = glm::vec3((position.x * CHUNK_X) + x, y, (position.z * CHUNK_Z) + z);
				//std::cout << "Actual chunkpos: " << position.x << ", " << position.z << std::endl;
				const BlockType currentBlock = GetBlock(x, y, z);
				if (currentBlock == AIR) continue;
				

				const BlockType southBlock = world->FindBlock(blockWorldPos.x, blockWorldPos.y, blockWorldPos.z + 1);
				const BlockType northBlock = world->FindBlock(blockWorldPos.x, blockWorldPos.y, blockWorldPos.z - 1);
				const BlockType eastBlock  = world->FindBlock(blockWorldPos.x + 1, blockWorldPos.y, blockWorldPos.z);
				const BlockType westBlock  = world->FindBlock(blockWorldPos.x - 1, blockWorldPos.y, blockWorldPos.z);
				const BlockType upBlock    = world->FindBlock(blockWorldPos.x, blockWorldPos.y + 1, blockWorldPos.z);
				const BlockType downBlock  = world->FindBlock(blockWorldPos.x, blockWorldPos.y - 1, blockWorldPos.z);

				/*std::cout << "Current Block: " << blockWorldPos.x << ", " << blockWorldPos.y << ", " << blockWorldPos.z << std::endl;
				std::cout << "  South Block: " << blockWorldPos.x << ", " << blockWorldPos.y << ", " << (blockWorldPos.z + 1) << std::endl;
				std::cout << "  North Block: " << blockWorldPos.x << ", " << blockWorldPos.y << ", " << (blockWorldPos.z - 1) << std::endl;
				std::cout << "   East Block: " << (blockWorldPos.x + 1) << ", " << blockWorldPos.y << ", " << blockWorldPos.z << std::endl;
				std::cout << "   West Block: " << (blockWorldPos.x - 1) << ", " << blockWorldPos.y << ", " << blockWorldPos.z << std::endl;
				std::cout << "     Up Block: " << blockWorldPos.x << ", " << (blockWorldPos.y + 1) << ", " << blockWorldPos.z << std::endl;
				std::cout << "   Down Block: " << blockWorldPos.x << ", " << (blockWorldPos.y - 1) << ", " << blockWorldPos.z << std::endl;*/

				unsigned char cullingFlag = 0;
				cullingFlag |= Block::IsTransparent(southBlock) ? 0 : CULL_POS_Z;
				cullingFlag |= Block::IsTransparent(northBlock) ? 0 : CULL_NEG_Z;
				cullingFlag |= Block::IsTransparent(eastBlock)	? 0 : CULL_POS_X;
				cullingFlag |= Block::IsTransparent(westBlock)	? 0 : CULL_NEG_X;
				cullingFlag |= Block::IsTransparent(upBlock)	? 0 : CULL_POS_Y;
				cullingFlag |= Block::IsTransparent(downBlock)	? 0 : CULL_NEG_Y;

				if ((cullingFlag & CULL_POS_Z) == 0) BlockGeneration::GenerateFace(chunkMesh.get(), currentBlock, blockWorldPos, SOUTH);
				if ((cullingFlag & CULL_NEG_Z) == 0) BlockGeneration::GenerateFace(chunkMesh.get(), currentBlock, blockWorldPos, NORTH);
				if ((cullingFlag & CULL_POS_X) == 0) BlockGeneration::GenerateFace(chunkMesh.get(), currentBlock, blockWorldPos, EAST);
				if ((cullingFlag & CULL_NEG_X) == 0) BlockGeneration::GenerateFace(chunkMesh.get(), currentBlock, blockWorldPos, WEST);
				if ((cullingFlag & CULL_POS_Y) == 0) BlockGeneration::GenerateFace(chunkMesh.get(), currentBlock, blockWorldPos, UP);
				if ((cullingFlag & CULL_NEG_Y) == 0) BlockGeneration::GenerateFace(chunkMesh.get(), currentBlock, blockWorldPos, DOWN);
			}
		}
	}
	BufferData();
	chunkReady = true;
}

BlockType Chunk::GetBlock(int x, int y, int z) const
{
	int localX = (x % CHUNK_X + CHUNK_X) % CHUNK_X;
	int localY = (y % CHUNK_Y + CHUNK_Y) % CHUNK_Y;
	int localZ = (z % CHUNK_Z + CHUNK_Z) % CHUNK_Z;
	unsigned int index = localX + (localY * CHUNK_X) + (localZ * CHUNK_X * CHUNK_Y);
	//std::cout << "Local Position: ("
		//<< localX << ", " << localY << ", " << localZ << ")" << std::endl;
	unsigned char blockID = blocks[index];
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