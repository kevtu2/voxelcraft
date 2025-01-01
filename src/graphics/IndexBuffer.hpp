#pragma once
#include <glad/glad.h>

class IndexBuffer
{
private:
	unsigned int bufferID;
	unsigned int count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return count; }
};