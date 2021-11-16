#pragma once
#include <SFML\Graphics.hpp>
#include "cereal.hpp"

struct Vec2f
{
	float x = 0;
	float y = 0;

	operator sf::Vector2f() const {
	
		return sf::Vector2f(x, y);
	};

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(x), CEREAL_NVP(y));
	}
};