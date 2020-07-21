#pragma once



class Tile
{
private:
	unsigned x, y;
	unsigned bombsAround;
	bool wasRevealed;
	bool isBomb;
	bool isFlag;
public:
	Tile(unsigned, unsigned);
	void setBomb();
	void setFlag();
	bool getIsBomb();
	bool getIsFlag();
	void setBombsAround(unsigned);
	bool canBeRevealed();
	bool getWasRevealed();
	void reveal();
	unsigned getBombsAround();
};

