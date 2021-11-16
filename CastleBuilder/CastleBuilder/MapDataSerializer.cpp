#include "MapDataSerializer.h"
#include <archives/xml.hpp>
#include <fstream>

MapData MapSerializer::LoadMapFromFile(const std::string& filePath)
{
	std::ifstream is(filePath);

	if (is.bad())
	{
		std::cout << "No Such A File or Directory"<<std::endl;
		assert(true);
		return MapData();
	}

	cereal::XMLInputArchive iarchive(is);

	MapData mapData;

	iarchive(mapData);

	return mapData;
}

void MapSerializer::SaveMapToFile(const MapData& mapData, const std::string& filePath)
{
	std::ofstream os(filePath + mapData.mapName);

	if (os.bad())
	{
		std::cout << "No Such A File or Directory" << std::endl;
		assert(true);
		return;
	}


	cereal::XMLOutputArchive archive(os);
	archive(CEREAL_NVP(mapData));
}
