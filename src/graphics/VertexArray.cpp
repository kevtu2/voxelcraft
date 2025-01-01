#include "VertexArray.hpp"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &arrayID);
	glBindVertexArray(arrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &arrayID);
}

void VertexArray::BindVertexBuffer(const VertexBuffer& vb, unsigned int layout) const
{
	vb.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);
}

void VertexArray::Bind() const
{
	glBindVertexArray(arrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
