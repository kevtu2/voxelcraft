#pragma once
#include <memory>
class UIManager
{
private:
	static UIManager Manager;
public:
	static UIManager& GetInstance();

	UIManager() = default;
	UIManager(const UIManager& other) = delete;
	void operator=(const UIManager&) = delete;
};

