#pragma once
#include <glad\glad.h>
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

class Renderer
{
public:
	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shaderProgram);
};