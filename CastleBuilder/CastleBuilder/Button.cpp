#include "Button.h"
#include "SFML\Window\Mouse.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\System\Vector2.hpp"
#include <cassert>
#include "SFML\Graphics\Texture.hpp"

Button::Button(const std::string& texturePath, const sf::Vector2f& size, const sf::Vector2f& position)
{
	if (texturePath.empty())
	{
		assert(("Not A Valid Texture Path!", true));
		return;
	}

	auto* mapTexture = new sf::Texture();
	mapTexture->loadFromFile(texturePath);
	buttonSprite = sf::RectangleShape(size);
	buttonSprite.setTexture(mapTexture);
	buttonSprite.setPosition(position);
	sf::Vector2f buttonScale = sf::Vector2f(mapTexture->getSize().x / size.x, mapTexture->getSize().y / size.y);
	buttonSprite.setScale(buttonScale);
	defaultScale = buttonSprite.getScale();
	buttonSprite.setOutlineColor(sf::Color::Black);
}

Button::~Button()
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!isVisible())
	{
		return;
	}

	target.draw(buttonSprite);
}

void Button::Update(const sf::RenderWindow& window)
{
	const auto mousePosition = sf::Mouse::getPosition(window);

	if (buttonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
	{
		OnHover();
		onHoverEvent();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			OnTap();
			onHoldEvent();
		}
		else
		{
			OnCancel();
			onCancelEvent();
		}
	}
	else
	{
		buttonSprite.setOutlineThickness(0);
	}
}

void Button::OnTap()
{
	buttonSprite.setScale(defaultScale * .95f);
}

void Button::OnCancel()
{
	buttonSprite.setScale(defaultScale);
}

void Button::OnHover()
{
	buttonSprite.setOutlineThickness(1.2f);
}
