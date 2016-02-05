#pragma once

#include "Entity.h"
#include <SFML\System.hpp>
#include "Toolbox.h"

class Worm : public Entity{
public:
	virtual ~Worm();
	virtual ENTITYTYPE getType(){ return WORM; }
	static Entity* createWorm(sf::Vector2f pos, b2World* world);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos(){ return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mSprite.getGlobalBounds().width; }
	virtual float getHeight(){ return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite(){ return mSprite; }
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual void addVector(sf::Vector2f &vector);
	virtual void move(sf::Vector2f &direction);
private:
	Worm(sf::Vector2f pos, b2World* world);

	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	bool mIsOnScreen = true;
	sf::RectangleShape mSpriteOutline;

	b2BodyDef mEntityBodyDef;
	b2Body* mBody;
	b2FixtureDef mFixtureDef;
	b2PolygonShape mBoxShape;
};

