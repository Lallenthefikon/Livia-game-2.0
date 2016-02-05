#pragma once

#include <SFML\System.hpp>
#include <Box2D\Box2D.h>

class Entity;
class Terrain;
//class Box2D;

struct Factory{
	static Entity* createPlayer(sf::Vector2f pos, b2World* world);
	static Terrain* createBlock0(sf::Vector2f pos, char type, b2World* world);
	static Entity* createWorm(sf::Vector2f pos, b2World* world);
};