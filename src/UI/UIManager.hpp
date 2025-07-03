#pragma once
#include <memory>
class UIManager
{
private:
	UIManager() = default;
	static UIManager Manager;

public:
	static UIManager& GetInstance();
	UIManager(const UIManager& other) = delete;
	void operator=(const UIManager&) = delete;
};

