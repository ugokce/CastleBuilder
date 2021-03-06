#include "GameScene.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "GameConfig.h"
#include <cassert>
#include "SFML\Graphics\RenderWindow.hpp"
#include "MapManager.h"
#include "Popup.h"
#include "GridTile.h"

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
	createShopPopupButton();
}

GameScene::~GameScene()
{
	if (shopPopup)
	{
		shopPopup->Close();
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

void GameScene::createShopPopupButton()
{
	const auto buttonPosition = sf::Vector2f(size.x * .8f, size.y * .8f);
	sf::Vector2f buttonSize = sf::Vector2f(size.x * .2f, size.y * .2f);
	shopButton = Button("../Textures/shop.png", buttonSize, buttonPosition);
	addChildObject(&shopButton);
	shopButton.onTapEvent.addListener(new EventListener([=]() {

		if (shopPopup)
		{
			if (shopPopup->isVisible())
			{
				shopPopup->hide();
			}
			else
			{
				shopPopup->show();
			}
		}
		else
		{
			openShopPopup();
		}

		}));
}

void GameScene::openShopPopup()
{
	sf::Vector2f popupSize = sf::Vector2f(size.x * .8f, size.y * .8f);
	sf::Vector2f popupPosition = sf::Vector2f(size.x * .5f, size.y * .5f);
	shopPopup = new Popup("../Textures/shopPopupBg.jpg", popupSize);
	shopPopup->setPosition(popupPosition);
	addChildObject(shopPopup);
}
