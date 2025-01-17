#include "BlockMesh.hpp"


//void BlockMesh::LoadVBO(std::vector<Vertex>& data, BlockType type, const glm::vec3 blockOffset)
//{
//	// If the block uses more than 1 texture, it's texture for the sides is the second pair (1,0)
//	// located inside textureCoords vector (in Block.cpp). If the block uses only 1, the
//	// texture coordinates in the texture atlas will just be the first and only pair (0)
//	Block block(type);
//	auto texturesUsed = block.GetTexturesUsed();
//	auto textureCoords = block.GetTextureCoords();
//	unsigned int currentTexCoord = (texturesUsed > 1) ? F_SIDE : 0;
//	char direction = 'n';
//
//	// Append faces to chunk VBO -- Vertex by vertex
//	for (size_t i = 0; i < 36; ++i)
//	{
//		// Which face is this currently drawing?
//		if (i >= 24 && i <= 29)
//			currentTexCoord = F_TOP;
//		else if (i > 29)
//			currentTexCoord = F_BOT;
//		if (i % 6 == 0)
//			direction = CUBE_FACE[i / 6];
//
//		// Append vertices of the face
//		unsigned int vertexIndex = CUBE_INDICES[i];
//		float xPos = CUBE_VERTICES[vertexIndex * 3 + 0] + blockOffset.x;
//		float yPos = CUBE_VERTICES[vertexIndex * 3 + 1] + blockOffset.y;
//		float zPos = CUBE_VERTICES[vertexIndex * 3 + 2] + blockOffset.z;
//		glm::vec3 positions = glm::vec3(xPos, yPos, zPos);
//
//		// Append texture coordinates
//		unsigned int uvIndex = CUBE_UV_INDICES[(i % 6)];
//		if (texturesUsed > 1)
//		{
//			float xUV = CUBE_UV_COORDS[uvIndex * 2 + 0] + textureCoords[currentTexCoord * 2 + 0] * SIZE_OF_TEXTURE;
//			float yUV = CUBE_UV_COORDS[uvIndex * 2 + 1] + textureCoords[currentTexCoord * 2 + 1] * SIZE_OF_TEXTURE;
//			glm::vec2 UV = glm::vec2(xUV, yUV);
//
//
//			Vertex vertex(positions, UV, direction, block.IsTransparent());
//			data.push_back(vertex);
//		}
//		else
//		{
//			float xUV = CUBE_UV_COORDS[uvIndex * 2 + 0] + textureCoords[0] * SIZE_OF_TEXTURE;
//			float yUV = CUBE_UV_COORDS[uvIndex * 2 + 1] + textureCoords[1] * SIZE_OF_TEXTURE;
//			glm::vec2 UV = glm::vec2(xUV, yUV);
//
//			Vertex vertex(positions, UV, direction, block.IsTransparent());
//			data.push_back(vertex);
//		}
//	}
//}

void BlockMesh::AddFace(ChunkMesh* chunkMesh, BlockType type, const glm::vec3 blockOffset, Face face)
{
	Block block(type);
	auto texCoords = block.GetTextureCoords();
	unsigned int texturesUsed = block.GetTexturesUsed();
	unsigned int faceIndex = static_cast<unsigned int>(face); // Quite a tragic solution but I'll just keep it

	// Generate 6 necessary vertices for one face
	for (int i = 0; i < 6; ++i)
	{
		// Generate position data
		unsigned int vertexIndex = CUBE_INDICES[(faceIndex * 6) + i];
		float xPos = CUBE_VERTICES[vertexIndex * 3 + 0] + blockOffset.x;
		float yPos = CUBE_VERTICES[vertexIndex * 3 + 1] + blockOffset.y;
		float zPos = CUBE_VERTICES[vertexIndex * 3 + 2] + blockOffset.z;
		glm::vec3 positions = glm::vec3(xPos, yPos, zPos);

		// Generate texture coordinates
		unsigned int uvIndex = CUBE_UV_INDICES[i];
		glm::vec2 UV = glm::vec2(1.0f);

		// TODO: Fix this hacky code :(!!
		if (texturesUsed > 1 && (face != DOWN || face != UP))
		{
			// Side faces
			float xUV = CUBE_UV_COORDS[uvIndex * 2 + 0] + texCoords[2] * SIZE_OF_TEXTURE;
			float yUV = CUBE_UV_COORDS[uvIndex * 2 + 1] + texCoords[3] * SIZE_OF_TEXTURE;
			UV = glm::vec2(xUV, yUV);
		}
		else if (texturesUsed > 1 && face == UP)
		{
			float xUV = CUBE_UV_COORDS[uvIndex * 2 + 0] + texCoords[0] * SIZE_OF_TEXTURE;
			float yUV = CUBE_UV_COORDS[uvIndex * 2 + 1] + texCoords[1] * SIZE_OF_TEXTURE;
			UV = glm::vec2(xUV, yUV);
		}
		else if (texturesUsed > 1 && face == DOWN)
		{
			float xUV = CUBE_UV_COORDS[uvIndex * 2 + 0] + texCoords[4] * SIZE_OF_TEXTURE;
			float yUV = CUBE_UV_COORDS[uvIndex * 2 + 1] + texCoords[5] * SIZE_OF_TEXTURE;
			UV = glm::vec2(xUV, yUV);
		}
		else
		{
			// If block only has one texture
			float xUV = CUBE_UV_COORDS[uvIndex * 2 + 0] + texCoords[0] * SIZE_OF_TEXTURE;
			float yUV = CUBE_UV_COORDS[uvIndex * 2 + 1] + texCoords[1] * SIZE_OF_TEXTURE;
			UV = glm::vec2(xUV, yUV);
		}
		
		Vertex vertex(positions, UV, CUBE_FACE[faceIndex], Block::IsTransparent(type));
		chunkMesh->chunkVertexData.push_back(vertex);

		unsigned int currentIndex = chunkMesh->vertexCount + FACE_INDICES[i];
		chunkMesh->chunkIndexData.push_back(currentIndex);
		// We add 4 unique vertices, but you need to specify texture coordinates for all 6 vertices that are used to draw
		// a square
		chunkMesh->vertexCount += 4;

	}
}


