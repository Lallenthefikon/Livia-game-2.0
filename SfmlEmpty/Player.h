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
	virtual sf::Vector2f getPos(){ return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mSprite.getLocalBounds().width; }
	virtual float getHeight(){ return mSprite.getLocalBounds().height; }
	virtual sf::Sprite getSprite(){ return mSprite; }
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual void addVector(sf::Vector2f &vector);
	virtual void move(sf::Vector2f &direction);
private:
	Player(sf::Vector2f pos);
	void move();
	float lerp(float goal, float current, float delta);
	void accelerateUp();
	void accelerateDown();
	void jump();
	void showCoords();
	sf::Vector2f mGravity, 
		mVelocity = sf::Vector2f(0, 0), 
		mVelocityGoal = sf::Vector2f(0, 0),
		mPosition,
		mSpriteOffset;
	sf::Sprite mSprite;
	float mPlayerSpeed;
	bool mIsOnScreen = true;
	bool mGrounded = false;
	sf::RectangleShape mSpriteOutline;
};

