#include "BlockGeneration.hpp"

void BlockGeneration::GenerateFace(std::unique_ptr<ChunkMesh> chunkMesh, BlockType type, const glm::vec3 blockOffset, Face face)
{
 	Block block(type);
	auto texCoords = block.GetTextureCoords();
	unsigned int texturesUsed = block.GetTexturesUsed();
	unsigned int faceIndex = static_cast<unsigned int>(face);

	// Generate 6 necessary vertices for one face
	// FIXME: We only need to generate 8 unique vertices then we can create indices from the CUBE_INDICES/FACE_INDICES
	// to properly draw the cube faces via glDrawElements(). So actually, we would only generate 4 vertices for each of the
	// cube's faces (6 * 4 = 24) vertices total. Then we let indices handle the rest of the drawing.
	for (int i = 0; i < 4; ++i)
	{
		// Determine block positions from cube data
		unsigned int vertexIndex = CUBE_INDICES[CUBE_UNIQUE_INDICES[i] + (faceIndex * 6)];
		float xPos = CUBE_VERTICES[vertexIndex * 3 + 0] + blockOffset.x;
		float yPos = CUBE_VERTICES[vertexIndex * 3 + 1] + blockOffset.y;
		float zPos = CUBE_VERTICES[vertexIndex * 3 + 2] + blockOffset.z;
		glm::vec3 positions = glm::vec3(xPos, yPos, zPos);

		// Determine block texture coordinates from cube data
		unsigned int uvIndex = i * 2;
		glm::vec2 UV = glm::vec2(1.0f);
		
		if (texturesUsed > 1 && (face != DOWN && face != UP))
		{
			// Side faces
			float u = CUBE_UV_COORDS[uvIndex + 0] + texCoords[2] * SIZE_OF_TEXTURE;
			float v = CUBE_UV_COORDS[uvIndex + 1] + texCoords[3] * SIZE_OF_TEXTURE;
			UV = glm::vec2(u, v);
		}
		else if (texturesUsed > 1 && face == UP)
		{
			float u = CUBE_UV_COORDS[uvIndex + 0] + texCoords[0] * SIZE_OF_TEXTURE;
			float v = CUBE_UV_COORDS[uvIndex + 1] + texCoords[1] * SIZE_OF_TEXTURE;
			UV = glm::vec2(u, v);
		}
		else if (texturesUsed > 1 && face == DOWN)
		{
			float u = CUBE_UV_COORDS[uvIndex + 0] + texCoords[4] * SIZE_OF_TEXTURE;
			float v = CUBE_UV_COORDS[uvIndex + 1] + texCoords[5] * SIZE_OF_TEXTURE;
			UV = glm::vec2(u, v);
		}
		else
		{
			// If block only has one texture
			float u = CUBE_UV_COORDS[uvIndex + 0] + texCoords[0] * SIZE_OF_TEXTURE;
			float v = CUBE_UV_COORDS[uvIndex + 1] + texCoords[1] * SIZE_OF_TEXTURE;
			UV = glm::vec2(u, v);
		}
		
		Vertex vertex(positions, UV);
		chunkMesh->chunkVertexData.push_back(vertex);
	}

	for (int i = 0; i < 6; ++i)
	{
		// Generate indices
		unsigned int currentIndex = chunkMesh->vertexCount + FACE_INDICES[i];
		chunkMesh->chunkIndexData.push_back(currentIndex);
	}
	// We add 4 unique vertices, but you need to specify texture coordinates for all 6 vertices that are used to draw a square
	chunkMesh->vertexCount += 4;
}
