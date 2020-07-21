#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <array>
#include <chrono>
#include "LogicManager.h"



class WindowDrawer
{
private:
	bool isGameLost;
	bool isGameWon;
	const unsigned TILE_SIZE = 21;
	unsigned mapSize;
	unsigned numberOfBombs;
	std::unique_ptr<LogicManager> logicManager;
	sf::Sprite buttonSprite;
	std::array<sf::Texture, 3> buttonTextures;
	sf::RenderWindow window;
	sf::Event event;
	std::array<sf::Texture, 12> textures;
	std::vector<std::vector<sf::Sprite>> sprites;
	sf::Vector2i localPosition;
	void initTextures();
	void initSprites();
	void initComponents();
	void checkMouse();
	void updateTiles(const std::vector<TileToChange>&);
	void drawTiles();
	void drawWindow();
	void restartGame();
public:
	WindowDrawer(unsigned, unsigned, const std::string&);
};

