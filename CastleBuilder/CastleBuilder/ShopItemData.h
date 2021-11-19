#pragma once

#include <string>
#include "Currency.h"

struct ShopItem
{
	std::string name;
	std::string description;
	std::string texturePath;
	Price cost;
	int levelCap = 0;
	int itemId = 0;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(name), CEREAL_NVP(description), CEREAL_NVP(cost), CEREAL_NVP(levelCap), 
			CEREAL_NVP(itemId), CEREAL_NVP(texturePath));
	}
};