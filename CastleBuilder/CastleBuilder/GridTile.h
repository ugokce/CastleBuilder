#pragma once
#include "SceneObject.h"
#include "GridData.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\ConvexShape.hpp"

class GridTile : public SceneObject
{
public:
	GridTile(const GridData& gridData, const sf::Vector2f&  gridPosition, 
		const sf::Vector2f& gridSize);
	// Inherited via SceneObject
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::ConvexShape shape;
	sf::RectangleShape buildingSprite;
	GridData data;
	sf::Vector2f position;
	sf::Vector2f size;

	void createBuildingImage();
};