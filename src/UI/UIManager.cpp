#include "UIManager.hpp"

UIManager& UIManager::GetInstance()
{
	static UIManager Manager;
	return Manager;
}
