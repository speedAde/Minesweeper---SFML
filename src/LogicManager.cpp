#include "LogicManager.h"



LogicManager::LogicManager(unsigned mapSize, unsigned numberOfBombs)
{
	this->mapSize = mapSize;
	tilesToReveal = mapSize * mapSize - numberOfBombs;
	isGameWon = false;
	tilesToChange.reserve(mapSize * mapSize);
	isTileToChange = false;
	LogicSetter setter(mapSize, numberOfBombs);
	tiles = setter.getTiles();
	startClock = clock();
}

bool LogicManager::clickOnATile(const sf::Vector2i& mousePosition, int mouseButtton) // 0/1 = PPM/LPM
{
	tilesToChange.clear();
	if (clock() - startClock  < 150)return false;
	startClock = clock();
	int x = mousePosition.x / TILE_SIZE;
	int y = mousePosition.y / TILE_SIZE;
	if (mouseButtton == 0)
	{
		if (x >= 0 && y >= 0 && x < mapSize && y < mapSize)
		{
			if (tiles[x][y].getWasRevealed() == false)
			{
				if (tiles[x][y].getIsFlag() == false)
				{
					tilesToChange.emplace_back(x, y, flag);
				}
				else
				{
					tilesToChange.emplace_back(x, y, unrevealed);
				}
				tiles[x][y].setFlag();
				return true;
			}
		}
	}
	else if (mouseButtton == 1)
	{
		if (x >= 0 && y >= 0 && x < mapSize && y < mapSize)
		{
			revealTile(x, y);
			return true;
		}
	}
	return false;
}

void LogicManager::revealTile(unsigned x, unsigned y)
{
	if (x >= 0 && y >= 0 && x < mapSize && y < mapSize)
	{
		if (tiles[x][y].canBeRevealed() == true)
		{
			if(tiles[x][y].getIsBomb() == true)
				tilesToChange.emplace_back(x, y, bomb);
			else
			{
				tilesToChange.emplace_back(x, y, tiles[x][y].getBombsAround());
				tilesToReveal--;
				if (tilesToReveal == 0)
					isGameWon = true;
			}
			tiles[x][y].reveal();
			if (tiles[x][y].getBombsAround() == 0 && tiles[x][y].getIsBomb() == false)
			{
				revealTile(x - 1, y - 1);
				revealTile(x - 1, y);
				revealTile(x - 1, y + 1);
				revealTile(x, y - 1);
				revealTile(x, y + 1);
				revealTile(x + 1, y - 1);
				revealTile(x + 1, y);
				revealTile(x + 1, y + 1);
			}
		}
	}
}

std::vector<TileToChange> LogicManager::getTilesToChange()
{
	return std::move(tilesToChange);
}

bool LogicManager::getIsGameWon()
{
	return isGameWon;
}