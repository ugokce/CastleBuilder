// CastleBuilder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <SFML\Graphics.hpp>
#include "ShopItemData.h"
#include <archives/xml.hpp>
#include <fstream>
#include "ShopData.h"
#include "Vec2f.h"
#include "GameScene.h"
#include "GameConfig.h"
#include "GridTile.h"
#include "MapData.h"
#include "Button.h"
#include "MapManager.h"

using namespace sf;

namespace
{
	constexpr auto texture_path = "../Textures/Map1.jpg";
	const Vector2<int> screenSize = { 1024, 768 };
	Vector2i mousePosition = {};
	bool isAnItemSelected = false;
	ConvexShape* selectedGrid = nullptr;
	bool IsZoomed = false;
	float defaultScale = 1.f;

	MapData mapData;
}

void SerializeShopItems()
{
	std::ofstream os(R"(C:\Users\Ugurcan\Desktop\data.xml)");
	cereal::XMLOutputArchive archive(os);

	Shop shopData;

	ShopItem item;
	item.cost = { 100, PriceType::Diamond };
	item.description = "sadasdasdasd";
	item.itemId = 10;
	item.levelCap = 10;
	item.name = "mahmut";

	ShopItem item2;
	item2.cost = { 100, PriceType::Silver };
	item2.description = "sadasdasdasd2";
	item2.itemId = 10;
	item2.levelCap = 10;
	item2.name = "mahmut2";

	ShopItem item3;
	item3.cost = { 100, PriceType::Gold };
	item3.description = "sadasdasdasd3";
	item3.itemId = 10;
	item3.levelCap = 10;
	item3.name = "mahmut3";

	std::vector<ShopItem> items = { item, item2, item3 };

	std::vector<ShopItem> items2 = { item2, item, item3 };

	shopData.shopItems[0] = items;
	shopData.shopItems[1] = items2;

	TabData tab;
	tab.name = "tab1";

	TabData tab2;
	tab.name = "tab2";

	shopData.tabs[0] = tab;
	shopData.tabs[1] = tab2;

	archive(CEREAL_NVP(shopData));
}

void SerializeGridTiles()
{
	std::ofstream os("../Maps/" + mapData.mapName +".xml");
	cereal::XMLOutputArchive archive(os);
	archive(CEREAL_NVP(mapData));
}

void SerializeGameConfig()
{
	GameConfigData config;
	config.mapsFolder = "../Maps";
	config.currentMapName = "firstMap.xml";

	std::ofstream os("../Config/Config.xml");
	cereal::XMLOutputArchive archive(os);
	archive(CEREAL_NVP(config));
}

int main()
{
	SerializeShopItems();

	SerializeGameConfig();
	

	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Castle Builder");

	GameScene currentScene(window);

	RectangleShape gridArea(Vector2f(screenSize.x * .75f, screenSize.y * .6f));
	gridArea.setOutlineColor(Color::Cyan);
	gridArea.setOutlineThickness(3.f);
	gridArea.setFillColor(Color::Transparent);
	gridArea.setPosition(screenSize.x * .1f, screenSize.y * .18f);

	//Background Map
	sf::RectangleShape backgroundSprite(sf::Vector2f(1024.f, 768.f));
	auto* mapTexture = new sf::Texture();
	mapTexture->loadFromFile(texture_path);
	backgroundSprite.setTexture(mapTexture);
	//Background Map

	sf::View view = window.getDefaultView();

	const Vector2f gridNodeSize = { 150, 100 };

	const int numberOfGridsCanFitInX = gridArea.getGlobalBounds().width / gridNodeSize.x;
	const int numberOfGridsCanFitInY = gridArea.getGlobalBounds().height / gridNodeSize.y;
	const float startPointX = gridNodeSize.x * .5f * numberOfGridsCanFitInX * .5f;
	const float startPointY = gridNodeSize.y * .5f * numberOfGridsCanFitInY * .5f;

	std::vector<ConvexShape> gridVector = {};

	mapData.size = { gridArea.getSize().x, gridArea.getSize().y };
	mapData.mapName = "firstMap";
	mapData.texturePath = "../Textures/Map1.jpg";

	const auto buttonPosition = sf::Vector2f(window.getSize().x * .8f, window.getSize().y * .8f);
	sf::Vector2f buttonSize = sf::Vector2f(window.getSize().x * .2f, window.getSize().y * .2f);
	auto serializeGridsButton = Button("../Textures/shop.png", buttonSize, buttonPosition);
	serializeGridsButton.onHoldEvent.addListener(new EventListener([=]() {

		//SerializeGridTiles();
	}));

	const auto& currentMap = MapManager::getInstance()->getMap();
	GridData denm;
	sf::Vector2f buttonSize2 = sf::Vector2f(window.getSize().x * .5f, window.getSize().y * .5f);
	denm.position = buttonSize2;
	GridTile tileDen(denm);


	for (int i = 0; i < numberOfGridsCanFitInX; i++)
	{
		for (int j = 0; j < numberOfGridsCanFitInY; j++)
		{


			sf::ConvexShape convex;
			convex.setPointCount(4);
			convex.setPoint(0, sf::Vector2f(75.f, 0.f));
			convex.setPoint(1, sf::Vector2f(150.f, 50.f));
			convex.setPoint(2, sf::Vector2f(75.f, 100.f));
			convex.setPoint(3, sf::Vector2f(0.f, 50.f));
			convex.setOutlineColor(sf::Color::Blue);
			convex.setFillColor(Color::Transparent);
			convex.setOutlineThickness(2.f);
			//convex.setScale(Vector2f(1 + (j * .1f), 1 + (j * .1f)));

			const float gridWidth = convex.getGlobalBounds().width;
			const float gridHeight = convex.getGlobalBounds().height;

			convex.setPosition(Vector2f(startPointX + (i * gridWidth * .5f), startPointY + (i * gridHeight * .5f) + (j * gridHeight)));

			gridVector.emplace_back(convex);

			GridData tileData;
			tileData.buildingId = 0;
			tileData.buildingTexturePath = "";
			tileData.position = convex.getPosition();
			tileData.scale = 1.f;
			mapData.grids.emplace_back(tileData);
		}
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Vector2i mousePositionDelta = Mouse::getPosition(window) - mousePosition;
		mousePosition = Mouse::getPosition(window);

		window.clear();
		window.setView(view);

		//Scene Draw And Update
		window.draw(currentScene);
		currentScene.update(window);

		//window.draw(backgroundSprite);
		//window.draw(gridArea);

		window.draw(serializeGridsButton);
		serializeGridsButton.Update(window);

		//ZOOM IN
		if (Keyboard::isKeyPressed(Keyboard::Z) && !IsZoomed)
		{
			IsZoomed = true;
			view.zoom(.75f);
			std::printf("zoom");
		}

		//ZOOM OUT
		if (Keyboard::isKeyPressed(Keyboard::X) && IsZoomed)
		{
			view.setSize(window.getDefaultView().getSize());
			std::printf("zoom out");
			IsZoomed = false;
		}

		/*for (auto& grid : gridVector)
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (grid.getGlobalBounds().contains(Vector2f(mousePosition.x, mousePosition.y)))
				{
					if (!isAnItemSelected)
					{
						selectedGrid = &grid;
					}
					
					isAnItemSelected = true;
				}
			}
			else
			{
				selectedGrid = nullptr;
				isAnItemSelected = false;
			}

			window.draw(grid);
		}

		if (selectedGrid)
		{
			selectedGrid->setPosition(Vector2f((float)mousePosition.x - selectedGrid->getGlobalBounds().width * .5f, (float)mousePosition.y - selectedGrid->getGlobalBounds().height * .5f));
		}*/
		
		window.display();
	}

	return 0;
}
