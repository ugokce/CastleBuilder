#pragma once

#include <string>

class Effect
{
public:
	std::string name;
	std::string description;
	std::string value;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(name, description, value);
	}
};