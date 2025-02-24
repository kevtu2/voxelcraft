#pragma once
#include <glad\glad.h>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "../blocks/Chunk.hpp"
#include "../blocks/Texture.hpp"
#include "../blocks/BlockGeneration.hpp"
#include "../graphics/Camera.hpp"
#include "../blocks/World.hpp"

class Renderer
{
public:
	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shaderProgram);
	static void DrawChunk(World* world, const Shader& shaderProgram, const Texture& texture, const Camera& player);
};