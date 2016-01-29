#pragma once

#include <SFML\Graphics.hpp>

class Entity{
public:
	enum ENTITYTYPE {PLAYER, WORM};
	Entity();
	virtual ~Entity();
	virtual ENTITYTYPE getType() = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
	virtual sf::Vector2f getPos() = 0;
	virtual sf::Vector2f getOffset() = 0;
	virtual void move(sf::Vector2f &direction) = 0;
	virtual void addVector(sf::Vector2f &vector) = 0;
	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
	virtual sf::Sprite getSprite() = 0;
	virtual bool isOnScreen() = 0;
};

