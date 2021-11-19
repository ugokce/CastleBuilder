#include "GameScene.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "GameConfig.h"
#include <cassert>
#include "SFML\Graphics\RenderWindow.hpp"
#include "MapManager.h"

GameScene::GameScene()
{
	createBackground();
}

GameScene::GameScene(const sf::RenderWindow& window)
{
	const auto buttonPosition = sf::Vector2f(window.getSize().x * .5f, window.getSize().y * .5f);
	sf::Vector2f buttonSize = sf::Vector2f(window.getSize().x * .2f, window.getSize().y * .2f);
	size = window.getDefaultView().getSize();

	createBackground();

	createGridTiles();
}

GameScene::~GameScene()
{
	objectsToDraw.clear();
}

void GameScene::update(const sf::RenderWindow& window)
{
	for (auto* childInScene : objectsToDraw)
	{
		childInScene->Update(window);
	}
}

void GameScene::addChildObject(SceneObject* child)
{
	objectsToDraw.emplace_back(child);
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mapBackground);

	for (auto* childInScene : objectsToDraw)
	{
		if (childInScene->isVisible())
		{
			target.draw(*childInScene);
		}
	}
}

void GameScene::createBackground()
{
	const auto& currentMap = MapManager::getInstance()->getMap();
	std::string mapTexturePath = currentMap.texturePath;

	if (mapTexturePath.empty())
	{
		mapTexturePath = "../Textures/Map1.jpg";
		assert(("Not A Valid Map Path!", true));
	}

	mapBackground = sf::RectangleShape(size);
	auto* mapTexture = new sf::Texture();
	mapTexture->loadFromFile(mapTexturePath);
	mapBackground.setTexture(mapTexture);
}

void GameScene::createGridTiles()
{
	const auto& currentMap = MapManager::getInstance()->getMap();
	gridTiles.reserve(currentMap.grids.size());

	for (const auto& gridData : currentMap.grids)
	{
		GridTile* tile = new GridTile(gridData);
		gridTiles.push_back(tile);
		addChildObject(tile);
	}
}
