#pragma once

#include "Vec2f.h"
#include "GridData.h"
#include <string>
#include <cereal/types/vector.hpp>

struct MapData
{
	Vec2f size;
	std::string texturePath;
	std::vector<GridData> grids;
	std::string mapName;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(size), CEREAL_NVP(texturePath), CEREAL_NVP(grids), CEREAL_NVP(mapName));
	}
};