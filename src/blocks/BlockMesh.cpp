#include "BlockMesh.hpp"

void BlockMesh::GenerateBlock(Chunk& chunk, const glm::vec3 blockOffset, const Block& block, const Texture& texture, const Shader& shaderProgram)
{
	auto textureCoords =  block.GetTextureInfo();
	unsigned int texturesUsed = block.GetTexturesUsed();
	
	// If the block uses more than 1 texture, it's texture for the sides is the second pair (1,0)
	// located inside textureInfo vector (in Block.cpp). If the block uses only 1, the
	// texture coordinates in the texture atlas will just be the first and only pair (0)
	unsigned int currentTexCoord = (texturesUsed > 1) ? F_SIDE : 0 ;

	// Append faces to chunk VBO -- Vertex by vertex
	for (size_t i = 0; i < 36; ++i)
	{
		// Which face is this currently drawing?
		if (i >= 24 && i <= 29)
			currentTexCoord = F_UP;
		else if (i > 29)
			currentTexCoord = F_DOWN;
			
		// Append vertices of the face
		unsigned int vertexIndex = CUBE_INDICES[i];

		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 0] + blockOffset.x);
		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 1] + blockOffset.y);
		chunk.AppendToVBO(CUBE_VERTICES[vertexIndex * 3 + 2] + blockOffset.z);

		// Append texture coordinates

		unsigned int uvIndex = CUBE_UV_INDICES[(i % 6)];
		chunk.AppendToVBO(CUBE_UV_COORDS[uvIndex * 2 + 0] + textureCoords[currentTexCoord * 2 + 0] * sizeOfTexture);
		chunk.AppendToVBO(CUBE_UV_COORDS[uvIndex * 2 + 1] + textureCoords[currentTexCoord * 2 + 1] * sizeOfTexture);
		
	}
}