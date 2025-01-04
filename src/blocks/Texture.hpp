#pragma once

class Texture
{
private:
	unsigned int numberOfRows;

	
public:
	Texture(const char* filename);
	Texture(unsigned int rows, const char* filename);
	~Texture();

	void Bind() const;
	void Unbind() const;
	unsigned int GetNumberOfRows() const { return numberOfRows; }
	
};