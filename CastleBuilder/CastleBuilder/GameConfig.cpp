#include "GameConfig.h"

static GameConfigManager* instance = nullptr;


const GameConfigManager* GameConfigManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameConfigManager();
	}

	return instance;
}

void GameConfigManager::LoadConfig()
{

}
