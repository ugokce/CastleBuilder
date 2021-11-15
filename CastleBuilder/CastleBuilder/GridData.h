#pragma once

#include "Vec2f.h"
#include "BuildingData.h"

struct GridData
{
	float scale;
	Vec2f position;
	int buildingId = 0;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(position), CEREAL_NVP(scale), CEREAL_NVP(buildingId));
	}
};
