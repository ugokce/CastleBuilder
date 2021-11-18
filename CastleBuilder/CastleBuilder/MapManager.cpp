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

void MapManager::loadMap()
{
	const std::string mapPath = GameConfigManager::getInstance()->getMapPath();
	const std::string currentMapName = GameConfigManager::getInstance()->getCurrentMapName();
	currentMap = MapSerializer::LoadMapFromFile(mapPath + "/" + currentMapName);

	const auto deneme = currentMap.texturePath;
}

void MapManager::updateGridData(const int gridId, const GridData& newGridData)
{
}

const MapManager* MapManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MapManager();
		instance->loadMap();
	}

	return instance;
}
