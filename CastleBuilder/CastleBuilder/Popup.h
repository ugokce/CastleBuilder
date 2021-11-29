#pragma once
#include "SceneObject.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/Transformable.hpp>
#include <string>

class Popup : public SceneObject, public sf::Transformable
{
public:
	Popup() = default;
	Popup(const sf::Vector2f& size);
	Popup(const std::string& backgroundTexturePath, const sf::Vector2f& size);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void setPosition(const sf::Vector2f& position);
	virtual void setOrigin(const sf::Vector2f& position);
	void Close();
	virtual void OnCreate();
private:
	sf::RectangleShape background;
};

