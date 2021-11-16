#pragma once
#include <string>
#include "cereal.hpp"

struct GameConfigData
{
	std::string mapsFolder;

	void operator = (const GameConfigData& other) 
	{
		if (this == &other)
			return;

		this->mapsFolder = other.mapsFolder;
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(mapsFolder));
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

	void LoadConfig();

	std::string defaultConfigPath = "../Config/Config.xml";

private:
	GameConfigData configData;
};