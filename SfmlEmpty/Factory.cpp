#include "Factory.h"
#include "Player.h"
#include "Block0.h"
#include "Worm.h"

Entity* Factory::createPlayer(sf::Vector2f pos, b2World* world) {
	return Player::createPlayer(pos, world);
}

Terrain* Factory::createBlock0(sf::Vector2f pos, char type, b2World* world) {
	return Block0::createBlock0(pos, type, world);
}

Entity* Factory::createWorm(sf::Vector2f pos, b2World* world) {
	return Worm::createWorm(pos, world);
}