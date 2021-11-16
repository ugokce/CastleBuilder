#include "MapManager.h"
#include "MapDataSerializer.h"
#include "GameConfig.h"

MapManager* instance = nullptr;

const MapData& MapManager::getMap() const
{
	return currentMap;
}

void MapManager::saveMap()
{
	const std::string mapPath = GameConfigManager::getInstance()->getMapPath();

	MapSerializer::SaveMapToFile(currentMap, mapPath);
}

void MapManager::updateGridData(const int gridId, const GridData& newGridData)
{
}

const MapManager* MapManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MapManager();
	}

	return instance;
}
