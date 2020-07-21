#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include "LogicSetter.h"
#include "Tile.h"



struct TileToChange
{
	TileToChange(unsigned x, unsigned y, int changeCode)
	{
		this->x = x; 
		this->y = y;
		this->changeCode = changeCode;
	}
	unsigned x, y;
	int changeCode;
};

enum changeCodes
{
	unrevealed = 9,
	bomb = 10,
	flag = 11
};

class LogicManager
{
private:
	const unsigned TILE_SIZE = 21;
	bool isTileToChange;
	bool isGameWon;
	unsigned mapSize;
	unsigned tilesToReveal;
	double startClock;
	std::vector<TileToChange> tilesToChange;
	std::vector<std::vector<Tile>> tiles;
	void revealTile(unsigned, unsigned);
public:
	LogicManager(unsigned, unsigned);
	bool clickOnATile(const sf::Vector2i&, int);
	bool getIsGameWon();
	std::vector<TileToChange> getTilesToChange();
};

