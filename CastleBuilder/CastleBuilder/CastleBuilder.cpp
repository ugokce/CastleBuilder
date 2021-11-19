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
#include <types/map.hpp>

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
	std::vector<ConvexShape> gridVector = {};
	MapData mapData;
}

void SerializeShopItems()
{
	std::ofstream os(R"(C:\Users\Ugurcan\Desktop\data.xml)");
	cereal::XMLOutputArchive archive(os);

	Shop shopData;

	ShopItem drugStore;
	drugStore.cost = { 10000, PriceType::Gold };
	drugStore.description = "Best Pharmacy";
	drugStore.itemId = 1;
	drugStore.levelCap = 2;
	drugStore.name = "Drugstore";
	drugStore.texturePath = "../Textures/workshop/drugstore.png";

	ShopItem government;
	government.cost = { 12900, PriceType::Gold };
	government.description = "Government Building";
	government.itemId = 2;
	government.levelCap = 3;
	government.name = "Government";
	government.texturePath = "../Textures/workshop/government.png";

	ShopItem museum;
	museum.cost = { 15999, PriceType::Gold };
	museum.description = "Museum Building";
	museum.itemId = 3;
	museum.levelCap = 3;
	museum.name = "Museum";
	museum.texturePath = "../Textures/workshop/museum.png";

	ShopItem propertyBuilding;
	propertyBuilding.cost = { 100000, PriceType::Gold };
	propertyBuilding.description = "Property Building";
	propertyBuilding.itemId = 4;
	propertyBuilding.levelCap = 6;
	propertyBuilding.name = "Property";
	propertyBuilding.texturePath = "../Textures/workshop/property.png";

	ShopItem temple;
	temple.cost = { 13000000, PriceType::Gold };
	temple.description = "Temple Building";
	temple.itemId = 5;
	temple.levelCap = 10;
	temple.name = "Temple";
	temple.texturePath = "../Textures/workshop/Temple-icon.png";

	std::vector<ShopItem> workshops = { drugStore, government, museum, propertyBuilding, temple};

	ShopItem bridge;
	bridge.cost = { 13200000, PriceType::Gold };
	bridge.description = "Bridge";
	bridge.itemId = 6;
	bridge.levelCap = 1;
	bridge.name = "Bridge";
	bridge.texturePath = "../Textures/decoration/government.png";

	ShopItem hangar;
	hangar.cost = { 1234900, PriceType::Gold };
	hangar.description = "Hangar Building";
	hangar.itemId = 7;
	hangar.levelCap = 3;
	hangar.name = "Hangar";
	hangar.texturePath = "../Textures/decoration/hangar.png";


	std::vector<ShopItem> decorations = { bridge, hangar};

	shopData.shopItems["Workshops"] = workshops;
	shopData.shopItems["Decorations"] = decorations;

	TabData tab;
	tab.name = "Workshops";

	TabData tab2;
	tab2.name = "Decorations";

	shopData.tabs["Workshops"] = tab;
	shopData.tabs["Decorations"] = tab2;

	archive(CEREAL_NVP(shopData));
}

void SerializeGridTiles()
{
	for (const auto& convex : gridVector)
	{
		GridData tileData;
		tileData.buildingId = 0;
		tileData.buildingTexturePath = "";
		tileData.position = convex.getPosition();
		tileData.scale = 1.f;
		mapData.grids.emplace_back(tileData);
	}

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

void CreateGridPositionEditor(const sf::FloatRect& gridArea)
{
	const Vector2f gridNodeSize = { 150, 100 };
	const int numberOfGridsCanFitInX = gridArea.width / gridNodeSize.x;
	const int numberOfGridsCanFitInY = gridArea.height / gridNodeSize.y;
	const float startPointX = gridNodeSize.x * .5f * numberOfGridsCanFitInX * .5f;
	const float startPointY = gridNodeSize.y * .5f * numberOfGridsCanFitInY * .5f;

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

			const float gridWidth = convex.getGlobalBounds().width;
			const float gridHeight = convex.getGlobalBounds().height;

			convex.setPosition(Vector2f(startPointX + (i * gridWidth * .5f), startPointY + (i * gridHeight * .5f) + (j * gridHeight)));

			gridVector.emplace_back(convex);
		}
	}
}

void HandleMouseClickOverGridPositionEditor(sf::RenderWindow& window)
{
	for (auto& grid : gridVector)
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
	}
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

	sf::View view = window.getDefaultView();


	CreateGridPositionEditor(gridArea.getGlobalBounds()); //Use this to place grids on the maps to their positions with your mouse


	mapData.size = { gridArea.getSize().x, gridArea.getSize().y };
	mapData.mapName = "firstMap";
	mapData.texturePath = "../Textures/Map1.jpg";

	const auto buttonPosition = sf::Vector2f(window.getSize().x * .8f, window.getSize().y * .8f);
	sf::Vector2f buttonSize = sf::Vector2f(window.getSize().x * .2f, window.getSize().y * .2f);
	auto serializeGridsButton = Button("../Textures/shop.png", buttonSize, buttonPosition);
	serializeGridsButton.onHoldEvent.addListener(new EventListener([=]() {

		//SerializeGridTiles(); //Save grid tile positions to xml file, I used it as like a grid editor
	}));


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

		//Scene Draw And Update, Grids and Scene Objects Will be Drawn in Scene
		window.draw(currentScene);
		currentScene.update(window);

		//window.draw(gridArea); //Showing the possible grid area

		//Grid Position Save Button
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

		//HandleMouseClickOverGridPositionEditor(window); //Draw and move grid position editor tiles
		
		window.display();
	}

	return 0;
}
