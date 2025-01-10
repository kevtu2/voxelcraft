#include "BlockMesh.hpp"

void BlockMesh::GenerateBlock(Chunk& chunk, const glm::vec3 blockOffset, const Block& block, const Texture& texture, const Shader& shaderProgram)
{
	auto textureCoords =  block.GetTextureInfo();
	unsigned int texturesUsed = block.GetTexturesUsed();
	// Append faces to chunk VBO -- Vertex by vertex
	for (size_t i = 0; i < 36; ++i)
	{
		// Append vertices of the face
		unsigned int vertexIndex = CUBE_INDICES[i];

		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 0] + blockOffset.x);
		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 1] + blockOffset.y);
		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 2] + blockOffset.z);

		// Append texture coordinates
		chunk.AppendToVBO(CUBE_UV_COORDS[(i % 4) * 2 + 0]);
		chunk.AppendToVBO(CUBE_UV_COORDS[(i % 4) * 2 + 1]);
	}
}
