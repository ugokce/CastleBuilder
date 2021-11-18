#pragma once
#include "SceneObject.h"
#include "GridData.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\ConvexShape.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "SFML\Graphics\Transformable.hpp"

class GridTile : public SceneObject
{
public:
	GridTile(const GridData& gridData);
	// Inherited via SceneObject
	virtual void draw(sf::RenderTarget& target, 
		sf::RenderStates states) const override;
	sf::FloatRect getGlobalBounds() const;
private:
	sf::ConvexShape shape;
	sf::RectangleShape buildingSprite;
	GridData data;

	sf::Vector2f position;
	float scale;
	void createBuildingImage();
};