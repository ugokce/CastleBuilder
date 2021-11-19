#include "GridTile.h"

GridTile::GridTile(const GridData& gridData)
{
	position = gridData.position;
	scale = gridData.scale;
	data = gridData;
	shape = sf::ConvexShape(4);
	shape.setPoint(0, sf::Vector2f(75.f, 0.f));
	shape.setPoint(1, sf::Vector2f(150.f, 50.f));
	shape.setPoint(2, sf::Vector2f(75.f, 100.f));
	shape.setPoint(3, sf::Vector2f(0.f, 50.f));
	shape.setOutlineColor(sf::Color::Blue);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(2.f);

	shape.setPosition(position);

	createBuildingImage();
}

void GridTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
	target.draw(buildingSprite);
}

sf::FloatRect GridTile::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

void GridTile::createBuildingImage()
{
	auto* mapTexture = new sf::Texture();
	mapTexture->loadFromFile(data.buildingTexturePath);
	sf::Vector2f textureSize = sf::Vector2f(mapTexture->getSize().x * scale, mapTexture->getSize().y * scale);
	buildingSprite = sf::RectangleShape(textureSize);
	buildingSprite.setTexture(mapTexture);
	buildingSprite.setPosition(position);
	sf::Vector2f spriteScale = sf::Vector2f(mapTexture->getSize().x * scale , mapTexture->getSize().y * scale);
	buildingSprite.setScale(spriteScale);
}
