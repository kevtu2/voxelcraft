#include "BlockMesh.hpp"

void BlockMesh::LoadVBO(std::vector<Vertex>& data, BlockType type, const glm::vec3 blockOffset)
{
	// If the block uses more than 1 texture, it's texture for the sides is the second pair (1,0)
	// located inside textureCoords vector (in Block.cpp). If the block uses only 1, the
	// texture coordinates in the texture atlas will just be the first and only pair (0)
	Block block(type);
	auto texturesUsed = block.GetTexturesUsed();
	auto textureCoords = block.GetTextureCoords();
	unsigned int currentTexCoord = (texturesUsed > 1) ? F_SIDE : 0;
	char direction = 'n';

	// Append faces to chunk VBO -- Vertex by vertex
	for (size_t i = 0; i < 36; ++i)
	{
		// Which face is this currently drawing?
		if (i >= 24 && i <= 29)
			currentTexCoord = F_TOP;
		else if (i > 29)
			currentTexCoord = F_BOT;
		if (i % 6 == 0)
			direction = CUBE_FACE[i / 6];

		// Append vertices of the face
		unsigned int vertexIndex = CUBE_INDICES[i];
		float xPos = CUBE_VERTICES[vertexIndex * 3 + 0] + blockOffset.x;
		float yPos = CUBE_VERTICES[vertexIndex * 3 + 1] + blockOffset.y;
		float zPos = CUBE_VERTICES[vertexIndex * 3 + 2] + blockOffset.z;
		glm::vec3 positions = glm::vec3(xPos, yPos, zPos);

		// Append texture coordinates
		unsigned int uvIndex = CUBE_UV_INDICES[(i % 6)];
		if (texturesUsed > 1)
		{
			float xUV = CUBE_UV_COORDS[uvIndex * 2 + 0] + textureCoords[currentTexCoord * 2 + 0] * SIZE_OF_TEXTURE;
			float yUV = CUBE_UV_COORDS[uvIndex * 2 + 1] + textureCoords[currentTexCoord * 2 + 1] * SIZE_OF_TEXTURE;
			glm::vec2 UV = glm::vec2(xUV, yUV);


			Vertex vertex(positions, UV, direction, block.IsTransparent());
			data.push_back(vertex);
		}
		else
		{
			float xUV = CUBE_UV_COORDS[uvIndex * 2 + 0] + textureCoords[0] * SIZE_OF_TEXTURE;
			float yUV = CUBE_UV_COORDS[uvIndex * 2 + 1] + textureCoords[1] * SIZE_OF_TEXTURE;
			glm::vec2 UV = glm::vec2(xUV, yUV);

			Vertex vertex(positions, UV, direction, block.IsTransparent());
			data.push_back(vertex);
		}
	}
}

void BlockMesh::AddFace(std::vector<Vertex>& data, BlockType type, const glm::vec3 blockOffset, Face faceIndex)
{
	// Generate 4 vertices for one face
	for (int i = 0; i < 4; ++i)
	{

	}
}


