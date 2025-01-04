#pragma once
#include <glad\glad.h>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

class VertexArray
{
private:
	unsigned int arrayID;

public:
	VertexArray();
	~VertexArray();

	void BindVertexBuffer(const VertexBuffer& vb) const;
	void Bind() const;
	void Unbind() const;


};