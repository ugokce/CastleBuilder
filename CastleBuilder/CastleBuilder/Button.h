#pragma once
#include "SceneObject.h"
#include <string>
#include <functional>
#include "SFML/Graphics/RectangleShape.hpp"
#include "Event.h"

class Button : public SceneObject
{
public:
	Button() = default;
	Button(const std::string& texturePath, const sf::Vector2f& size, 
		const sf::Vector2f& position);
	~Button();

	// Inherited via SceneObject
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update(const sf::RenderWindow& window);

	Event onHoldEvent;
	Event onCancelEvent;
	Event onHoverEvent;

private:
	sf::RectangleShape buttonSprite;

	void OnTap();
	void OnCancel();
	void OnHover();

	sf::Vector2f defaultScale;
};