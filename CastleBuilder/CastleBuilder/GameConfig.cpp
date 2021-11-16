#include "GameConfig.h"
#include <archives/xml.hpp>
#include <fstream>
#include <assert.h>

static GameConfigManager* instance = nullptr;

GameConfigManager* GameConfigManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameConfigManager();
	}

	return instance;
}

void GameConfigManager::LoadConfig()
{
	const std::string& configPath = getInstance()->defaultConfigPath;

	std::ifstream is(configPath);

	if (is.bad())
	{
		std::cout << "No Such A File or Directory" << std::endl;
		assert(true);
	}

	cereal::XMLInputArchive iarchive(is);

	GameConfigData newConfig;

	iarchive(newConfig);

	getInstance()->configData = newConfig;
}
