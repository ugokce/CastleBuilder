#pragma once
#include <SFML\Graphics.hpp>

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
		archive(x, y);
	}
};