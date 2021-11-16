#pragma once
#include <string>
#include "cereal.hpp"

struct GameConfigData
{
	std::string mapsFolder;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(mapsFolder));
	}
};


class GameConfigManager
{
public:
	static const GameConfigManager* getInstance();

	const std::string& getMapPath() const
	{
		return configData.mapsFolder;
	}

	void LoadConfig();

private:
	GameConfigData configData;
};