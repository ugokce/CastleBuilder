#pragma once

#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include "ShopItemData.h"

struct TabData
{
	std::string name;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(name));
	}
};

struct Shop
{
	std::map<int, TabData> tabs;
	std::map<int, std::vector<ShopItem>> shopItems;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(tabs), CEREAL_NVP(shopItems));
	}
};