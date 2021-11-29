#include "Popup.h"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\RenderTarget.hpp"

Popup::Popup(const sf::Vector2f& size)
{
	Popup("", size);
}

Popup::Popup(const std::string& backgroundTexturePath, const sf::Vector2f& size)
{
	background = sf::RectangleShape(size);
	background.setOrigin(size * .5f);
	auto* bgTexture = new sf::Texture();
	bgTexture->loadFromFile(backgroundTexturePath);
	background.setTexture(bgTexture);
}

void Popup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isVisible())
	{
		target.draw(background);
	}
}

void Popup::setPosition(const sf::Vector2f& position)
{
	Transformable::setPosition(position);
	background.setPosition(position);
}

void Popup::setOrigin(const sf::Vector2f& position)
{
	Transformable::setOrigin(position);
	background.setOrigin(position);
}

void Popup::Close()
{
	delete this;
}

void Popup::OnCreate()
{
}
