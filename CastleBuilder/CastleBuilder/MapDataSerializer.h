#pragma once

#include "MapData.h"
#include <string>


class MapSerializer
{
public:
	static MapData LoadMapFromFile(const std::string& filePath);
	static void SaveMapToFile(const MapData& mapData, const std::string& filePath);
};