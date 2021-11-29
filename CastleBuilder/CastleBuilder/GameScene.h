#pragma once

#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SceneObject.h"
#include <vector>
#include "Button.h"

class Popup;
class Button;
class GridTile;

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
	std::vector<GridTile*> gridTiles;
	sf::Vector2f size;
	Button shopButton;
	Popup* shopPopup = nullptr;

	void createBackground();
	void createGridTiles();
	void createShopPopupButton();
	void openShopPopup();
};