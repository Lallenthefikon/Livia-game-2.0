#pragma once

#include <SFML\System.hpp>
#include "Entity.h"
#include "Toolbox.h"

class Player : public Entity{
public:
	virtual ~Player();
	virtual Entity::ENTITYTYPE getType(){ return PLAYER; }
	static Entity* createPlayer(sf::Vector2f pos);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos(){ return mPosition; }
	virtual float getWidth(){ return mSprite.getGlobalBounds().width; }
	virtual float getHeight(){ return mSprite.getGlobalBounds().height; }
	virtual void addVector(sf::Vector2f &vector);
private:
	Player(sf::Vector2f pos);
	void move();
	float lerp(float goal, float current, float delta);
	void accelerateUp();
	void accelerateDown();
	sf::Vector2f mPosition, mGravity, mVelocity = sf::Vector2f(0, 0), mVelocityGoal = sf::Vector2f(0, 0);
	sf::Sprite mSprite;
};

