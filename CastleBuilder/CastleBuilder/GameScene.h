#pragma once

#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SceneObject.h"
#include <vector>

namespace sf
{
	class RenderTarget;
	class RenderWindow;
}

class GameScene : public sf::Drawable
{
public:
	GameScene();
	~GameScene();
	void update(const sf::RenderWindow& window);
protected:
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<SceneObject*> objectsToDraw;
	sf::Sprite mapBackground;

	void createBackground();
};