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

void VertexArray::BindVertexBuffer(const VertexBuffer& vb) const
{
	vb.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
}

void VertexArray::Bind() const
{
	glBindVertexArray(arrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
