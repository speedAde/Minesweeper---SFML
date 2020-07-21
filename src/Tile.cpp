#include "Tile.h"


Tile::Tile(unsigned x, unsigned y)
{
	this->x = x;
	this->y = y;
	isBomb = false;
	isFlag = false;
	wasRevealed = false;
	bombsAround = 0;
}

void Tile::setBomb()
{
	isBomb = true;
}

void Tile::setBombsAround(unsigned bombsAround)
{
	this->bombsAround = bombsAround;
}

bool Tile::canBeRevealed()
{
	if (isFlag || wasRevealed) return false;
	return true;
}

bool Tile::getIsBomb()
{
	return isBomb;
}

bool Tile::getIsFlag()
{
	return isFlag;
}

bool Tile::getWasRevealed()
{
	return wasRevealed;
}

unsigned Tile::getBombsAround()
{
	return bombsAround;
}

void Tile::setFlag()
{
	if (isFlag == false)
		isFlag = true;
	else
		isFlag = false;
}

void Tile::reveal()
{
	wasRevealed = true;
}