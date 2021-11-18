#include "GridTile.h"

GridTile::GridTile(const GridData& gridData, const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize) : data(gridData), position(gridPosition), size(gridSize)
{
	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(75.f, 0.f));
	shape.setPoint(1, sf::Vector2f(150.f, 50.f));
	shape.setPoint(2, sf::Vector2f(75.f, 100.f));
	shape.setPoint(3, sf::Vector2f(0.f, 50.f));
	shape.setOutlineColor(sf::Color::Blue);
	shape.setFillColor(sf::Color::Transparent);
	shape.setPosition(position);

	createBuildingImage();
}

void GridTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
	target.draw(buildingSprite);
}

void GridTile::createBuildingImage()
{
	auto* mapTexture = new sf::Texture();
	mapTexture->loadFromFile(data.buildingTexturePath);
	buildingSprite = sf::RectangleShape(size);
	buildingSprite.setTexture(mapTexture);
	buildingSprite.setPosition(position);
	sf::Vector2f spriteScale = sf::Vector2f(mapTexture->getSize().x / size.x * .9f, mapTexture->getSize().y / size.y * .9f);
	buildingSprite.setScale(spriteScale);
}
