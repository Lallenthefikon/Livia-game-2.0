#pragma once

#include "Entity.h"
#include <SFML\System.hpp>
#include "Toolbox.h"

class Worm : public Entity{
public:
	virtual ~Worm();
	virtual ENTITYTYPE getType(){ return WORM; }
	static Entity* createWorm(sf::Vector2f pos);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos(){ return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mSprite.getGlobalBounds().width; }
	virtual float getHeight(){ return mSprite.getGlobalBounds().height; }
	virtual void addVector(sf::Vector2f &vector);
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual void collided(std::string &direction);
	virtual void correctPosition(sf::Vector2f &direction);
private:
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;
	Worm(sf::Vector2f pos);
	bool mIsOnScreen = true;
};

