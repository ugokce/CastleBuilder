#include "GameScene.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "GameConfig.h"
#include <cassert>

GameScene::GameScene()
{
	createBackground();
}

GameScene::~GameScene()
{
	for (auto* childInScene : objectsToDraw)
	{
		delete childInScene;
	}

	objectsToDraw.clear();
}

void GameScene::update(const sf::RenderWindow& window)
{
	for (auto* childInScene : objectsToDraw)
	{
		childInScene->Update(window);
	}
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
	const std::string& mapTexturePath = GameConfigManager::getInstance()->getMapPath();

	if (mapTexturePath.empty())
	{
		assert(("Not A Valid Map Path!", true));
		return;
	}

	sf::Texture mapTexture;
	mapTexture.loadFromFile(mapTexturePath);
	mapBackground.setTexture(mapTexture);
}
