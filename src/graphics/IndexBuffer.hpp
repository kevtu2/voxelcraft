#pragma once
#include <glad/glad.h>

class IndexBuffer
{
private:
	unsigned int bufferID;

public:
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();

	void Bind();
	void Unbind();
};