#pragma once

#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SceneObject.h"
#include <vector>
#include "Button.h"
#include "GridTile.h"

namespace sf
{
	class RenderTarget;
	class RenderWindow;
}

class GameScene : public sf::Drawable
{
public:
	GameScene();
	GameScene(const sf::RenderWindow& window);
	~GameScene();
	void update(const sf::RenderWindow& window);
	void addChildObject(SceneObject* child);
protected:
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<SceneObject*> objectsToDraw;
	sf::RectangleShape mapBackground;
	//Button denemeButton;
	std::vector<GridTile> gridTiles;
	sf::Vector2f size;

	void createBackground();
	void createGridTiles();
};