#pragma once
#include <random>
#include <numeric>
#include <vector>
#include "Tile.h"


class LogicSetter
{
private:
	unsigned mapSize;
	unsigned numberOfBombs;
	std::vector<std::vector<Tile>> tiles;
	void initTiles();
	void setBombsRandomly();
	unsigned calculateBombsAround(unsigned, unsigned);
public:
	LogicSetter(unsigned, unsigned);
	std::vector<std::vector<Tile>> getTiles();
};

