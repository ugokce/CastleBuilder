#pragma once
#include "SFML\Graphics\Drawable.hpp"

namespace sf
{
	class RenderTarget;
	class RenderWindow;
}

class SceneObject : public sf::Drawable
{
public:
	bool isVisible() const
	{
		return visible;
	}

	void hide()
	{
		visible = true;
	}

	void show()
	{
		visible = false;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	virtual void Update(const sf::RenderWindow& window)
	{}

private:
	bool visible = true;
};