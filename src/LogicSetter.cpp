#include "LogicSetter.h"




LogicSetter::LogicSetter(unsigned mapSize, unsigned numberOfBombs)
{
	this->mapSize = mapSize;
	this->numberOfBombs = numberOfBombs;
	initTiles();
}

void LogicSetter::initTiles()
{
	tiles.resize(mapSize);
	for (unsigned i = 0; i < mapSize; ++i)
	{
		tiles[i].reserve(mapSize);
		for (unsigned j = 0; j < mapSize; ++j)
			tiles[i].emplace_back(Tile(i, j));
	}
	setBombsRandomly();
	
	for (unsigned i = 0; i < mapSize; ++i)
	{
		for (unsigned j = 0; j < mapSize; ++j)
			tiles[i][j].setBombsAround(calculateBombsAround(i, j));
	}
}

void LogicSetter::setBombsRandomly()
{
	std::random_device randomDevice;
	std::mt19937 seed(randomDevice());
	std::vector<unsigned> position(mapSize * mapSize);
	std::iota(position.begin(), position.end(), 0);
	std::shuffle(position.begin(), position.end(), seed);

	for (unsigned i = 0; i < numberOfBombs; ++i)
	{
		tiles[position[i] / mapSize][position[i] % mapSize].setBomb();
	}
}

unsigned LogicSetter::calculateBombsAround(unsigned x, unsigned y)
{
	unsigned counter = 0;

	if (y > 0)
	{
		if (tiles[x][y - 1].getIsBomb())counter++;
		if (x > 0)
		{
			if (tiles[x - 1][y - 1].getIsBomb())counter++;
		}
		if (x + 1 < mapSize)
		{
			if (tiles[x + 1][y - 1].getIsBomb())counter++;
		}
	}

	if (y  + 1 < mapSize)
	{
		if (tiles[x][y + 1].getIsBomb())counter++;
		if (x > 0)
		{
			if (tiles[x - 1][y + 1].getIsBomb())counter++;
		}
		if (x + 1 < mapSize)
		{
			if (tiles[x + 1][y + 1].getIsBomb())counter++;
		}
	}

	if (x > 0)
	{
		if (tiles[x - 1][y].getIsBomb())counter++;
	}
	if (x + 1 < mapSize)
	{
		if (tiles[x + 1][y].getIsBomb())counter++;
	}
	return counter;
}

std::vector<std::vector<Tile>> LogicSetter::getTiles()
{
	return std::move(tiles);
}