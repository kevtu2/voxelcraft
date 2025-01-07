#include "BlockMesh.hpp"

void BlockMesh::GenerateBlockFaceMesh(Chunk& chunk, const glm::vec3 blockOffset, const Block& block, const Texture& texture, const Shader& shaderProgram)
{
	auto textureCoords =  block.GetTextureInfo();
	unsigned int texturesUsed = block.GetTexturesUsed();

	// Append faces to chunk VBO -- Vertex by vertex
	for (size_t i = 0; i < 6; ++i)
	{
		// Append vertices of the face
		chunk.AppendToChunk(CUBE_VERTICES[CUBE_INDICES[i * 3 + 0]] + blockOffset.x);
		chunk.AppendToChunk(CUBE_VERTICES[CUBE_INDICES[i * 3 + 1]] + blockOffset.y);
		chunk.AppendToChunk(CUBE_VERTICES[CUBE_INDICES[i * 3 + 2]] + blockOffset.z);

		// Append texture coordinates
		chunk.AppendToChunk(CUBE_UV_COORDS[CUBE_INDICES[i * 2 + 0]] + textureCoords[i + 0]);
		chunk.AppendToChunk(CUBE_UV_COORDS[CUBE_INDICES[i * 2 + 1]] + textureCoords[i + 1]);
	}
	
}
