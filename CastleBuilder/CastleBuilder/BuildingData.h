#pragma once
#include <string>
#include "Effect.h"
#include "Currency.h"

struct BuildingData
{
	int buildingId = 0;
	std::string name;
	std::string imagePath;
	Price cost;
	Effect effect;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(buildingId), CEREAL_NVP(name), CEREAL_NVP(imagePath), CEREAL_NVP(cost), CEREAL_NVP(effect));
	}
};
