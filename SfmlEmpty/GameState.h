#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Box2D\Box2D.h>

class GameState{
public:
	GameState();
	~GameState();
	virtual void update(sf::RenderWindow &window) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void loadMap() = 0;
	virtual void setCurrentMap(std::string &mapname) = 0;
};

