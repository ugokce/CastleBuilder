#pragma once
#include "MapData.h"


class MapManager
{
public:
	static const MapManager* getInstance();
	const MapData& getMap() const;
	void saveMap();
	void loadMap();
	void updateGridData(const int gridId, const GridData& newGridData);
private:
	MapData currentMap;
};