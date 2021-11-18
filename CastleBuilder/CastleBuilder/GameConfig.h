#pragma once
#include <string>
#include "cereal.hpp"

struct GameConfigData
{
	std::string mapsFolder;
	std::string currentMapName;

	void operator = (const GameConfigData& other) 
	{
		if (this == &other)
			return;

		this->mapsFolder = other.mapsFolder;
		this->currentMapName = other.currentMapName;
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(mapsFolder), CEREAL_NVP(currentMapName));
	}
};


class GameConfigManager
{
public:
	static GameConfigManager* getInstance();

	const std::string& getMapPath() const
	{
		return configData.mapsFolder;
	}

	const std::string& getCurrentMapName() const
	{
		return configData.currentMapName;
	}

	void LoadConfig();

	std::string defaultConfigPath = "../Config/Config.xml";

private:
	GameConfigData configData;
};