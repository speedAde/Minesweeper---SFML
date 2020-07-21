#include "WindowDrawer.h"



WindowDrawer::WindowDrawer(unsigned mapSize, unsigned numberOfBombs, const std::string& windowName)
{
	isGameWon = false;
	isGameLost = false;
	this->mapSize = mapSize;
	this->numberOfBombs = numberOfBombs;
	window.create(sf::VideoMode(TILE_SIZE * mapSize, TILE_SIZE * mapSize + 30), windowName);
	logicManager = std::make_unique<LogicManager>(mapSize, numberOfBombs);
	initComponents();
	drawWindow();
}
void WindowDrawer::initComponents()
{
	initTextures();
	initSprites();
}

void WindowDrawer::initTextures()
{
	for (int i = 0; i < 12; ++i)
	{
		textures[i].loadFromFile("textures/texture" + std::to_string(i) + ".png");
		// 0 - 8 number of bombs around, 9 - default, 10 - bomb, 11 - flag
	}

	buttonTextures[0].loadFromFile("textures/restart.png");
	buttonTextures[1].loadFromFile("textures/lost.png");
	buttonTextures[2].loadFromFile("textures/win.png");
}

void WindowDrawer::initSprites()
{
	sprites.resize(mapSize);
	for (unsigned i = 0; i < mapSize; ++i)
		sprites[i].resize(mapSize);
	for (unsigned i = 0; i < mapSize; ++i)
	{
		for (unsigned j = 0; j < mapSize; ++j)
		{
			sprites[i][j].setPosition(i * TILE_SIZE, j * TILE_SIZE);
			sprites[i][j].setTexture(textures[9]); // 9 - default
		}
	}

	buttonSprite.setTexture(buttonTextures[0]);
	buttonSprite.setPosition(0, TILE_SIZE * mapSize);
}

void WindowDrawer::drawTiles()
{
	for (unsigned i = 0; i < mapSize; ++i)
	{
		for (unsigned j = 0; j < mapSize; ++j)
		{
			window.draw(sprites[i][j]);
		}
	}
}

void WindowDrawer::checkMouse()
{
	localPosition = sf::Mouse::getPosition(window);
	if (localPosition.y > TILE_SIZE * mapSize && localPosition.y > 0)
	{
		if (localPosition.y < TILE_SIZE * mapSize + 30)
		{
			if (localPosition.x >= 0 && localPosition.x <= TILE_SIZE * mapSize)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					restartGame();
			}
		}
	}
	if (!isGameLost && !isGameWon)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (logicManager->clickOnATile(localPosition, 1))
			{
				updateTiles(logicManager->getTilesToChange());
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (logicManager->clickOnATile(localPosition, 0))
			{
				updateTiles(logicManager->getTilesToChange());
			}
		}
	}
	else if(isGameLost)
	{
		buttonSprite.setTexture(buttonTextures[1]);
	}
	else
	{
		buttonSprite.setTexture(buttonTextures[2]);
	}

}

void WindowDrawer::updateTiles(const std::vector<TileToChange>& tilesToChange)
{
	for (unsigned i = 0; i < tilesToChange.size(); ++i)
	{
		sprites[tilesToChange[i].x][tilesToChange[i].y]
			.setTexture(textures[tilesToChange[i].changeCode]);
		if (tilesToChange[i].changeCode == bomb)
		{
			isGameLost = true;
		}
	}
	if (logicManager->getIsGameWon())
		isGameWon = true;
}

void WindowDrawer::restartGame()
{
	for (unsigned i = 0; i < mapSize; ++i)
	{
		for (unsigned j = 0; j < mapSize; ++j)
		{
			sprites[i][j].setTexture(textures[9]); // 9 - default
		}
	}
	isGameLost = false;
	isGameWon = false;
	buttonSprite.setTexture(buttonTextures[0]);
	logicManager = std::make_unique<LogicManager>(mapSize, numberOfBombs);
}

void WindowDrawer::drawWindow()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		checkMouse();
		window.clear();
		drawTiles();
		window.draw(buttonSprite);
		window.display();
	}
}