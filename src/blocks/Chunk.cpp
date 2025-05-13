#include "Chunk.hpp"
#include "World.hpp"


Chunk::Chunk()
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	position = glm::vec3(0, 0, 0);
	chunkMesh = std::make_unique<ChunkMesh>();
}

Chunk::Chunk(int x, int y, int z)
	: position(glm::vec3(x, y, z))
{
	glGenBuffers(1, &chunkVBO_ID);
	glGenBuffers(1, &chunkIBO_ID);
	glGenVertexArrays(1, &chunkVAO_ID);
	chunkMesh = std::make_unique<ChunkMesh>();
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


void Chunk::GenerateBlockData(World* world)
{
	for (int x = 0; x < CHUNK_X; ++x)
	{
		for (int z = 0; z < CHUNK_Z; ++z)
		{
			float rawNoise = world->GetNoise(position.x * CHUNK_X + x, position.z * CHUNK_Z + z); // -1 to 1
			float normalized = (rawNoise * 0.5f + 0.5f); // 0 to 1
			int height = static_cast<int>(normalized * surfaceY);



			for (int y = 0; y <= height; ++y)
			{
				unsigned int index = x + (y * CHUNK_X) + (z * CHUNK_X * CHUNK_Y);
				blocks[index] = static_cast<unsigned char>(BlockType::DIRT);
			}
		}
	}

	for (int i = 0; i < blocks.size(); ++i)
	{
		if (blocks[i] == 205) blocks[i] = BlockType::AIR;
	}
}

void Chunk::GenerateChunkMesh(World* world)
{
	chunkMesh->Clear();
	for (int x = 0; x < CHUNK_X; ++x)
	{
		for (int z = 0; z < CHUNK_Z; ++z)
		{
			float rawNoise = world->GetNoise(position.x * CHUNK_X + x, position.z * CHUNK_Z + z); // -1 to 1
			float normalized = (rawNoise * 0.5f + 0.5f); // 0 to 1
			int height = static_cast<int>(normalized * surfaceY);

			for (int y = 0; y <= height; ++y)
			{
				glm::vec3 blockWorldPos = glm::vec3((position.x * CHUNK_X) + x, y, (position.z * CHUNK_Z) + z);

				const BlockType currentBlock = GetBlock(blockWorldPos.x, y, blockWorldPos.z);
				if (currentBlock == AIR) continue;

				const BlockType southBlock	= world->FindBlock(blockWorldPos.x, blockWorldPos.y, blockWorldPos.z + 1);
				const BlockType northBlock	= world->FindBlock(blockWorldPos.x, blockWorldPos.y, blockWorldPos.z - 1);
				const BlockType eastBlock	= world->FindBlock(blockWorldPos.x + 1, blockWorldPos.y, blockWorldPos.z);
				const BlockType westBlock	= world->FindBlock(blockWorldPos.x - 1, blockWorldPos.y, blockWorldPos.z);
				const BlockType upBlock		= world->FindBlock(blockWorldPos.x, blockWorldPos.y + 1, blockWorldPos.z);
				const BlockType downBlock	= world->FindBlock(blockWorldPos.x, blockWorldPos.y - 1, blockWorldPos.z);

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
	if (y < 0) return BlockType::AIR;
	else if (y > CHUNK_Y - 1) return BlockType::AIR;

	int localX = x - (position.x * CHUNK_X);
	int localY = y;
	int localZ = z - (position.z * CHUNK_Z);
	unsigned int index = localX + (localY * CHUNK_X) + (localZ * CHUNK_X * CHUNK_Y);
	unsigned char blockID = blocks[index];

	return Block::GetBlockTypeFromID(blockID);
}
