#pragma once
// Define hasher for glm::vec2 used for unordered_map (activeChunks)
struct Vec2Hasher
{
	std::size_t operator()(const glm::vec2& c) const
	{
		// XOR hashes of x and z in chunkPos
		return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
	}
};

struct Vec2Equals
{
	bool operator()(const glm::vec2& lhs, const glm::vec2& rhs) const
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
};