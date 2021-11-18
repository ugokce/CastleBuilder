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

	denemeButton = Button("../Textures/shop.png", buttonSize, buttonPosition);
	addChildObject(&denemeButton);
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
		target.draw(*childInScene);
	}
}

void GameScene::createBackground()
{
	/*const std::string& mapTexturePath = GameConfigManager::getInstance()->getMapPath();
	const auto& currentMap = MapManager::getInstance()->getMap();

	if (mapTexturePath.empty())
	{
		assert(("Not A Valid Map Path!", true));
		return;
	}*/

	mapBackground = sf::RectangleShape(size);
	auto* mapTexture = new sf::Texture();
	mapTexture->loadFromFile("../Textures/Map1.jpg");
	mapBackground.setTexture(mapTexture);
}
