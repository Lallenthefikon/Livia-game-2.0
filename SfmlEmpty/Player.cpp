#include "Player.h"
#include <iostream>

static float timeElapsed = 0.1666666666666667;
static float jumpVelocity = -375;

Player::Player(sf::Vector2f pos) :
mPlayerSpeed(30),
mNrofJumpsLeft(3){
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::PLAYERTEXTURE), sf::IntRect(0,0,120,140));
	mSprite.setTexture(mTexture);
	mSpriteOffset = sf::Vector2f(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);

	Toolbox::copyPlayerInfo(mSprite);
}


Player::~Player(){
}

Entity* Player::createPlayer(sf::Vector2f pos){
	return new Player(pos);
}

void Player::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

void Player::update(){
	move();
	Toolbox::copyPlayerInfo(mSprite);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
		showCoords();
	}
}

void Player::move() {

	speedModifier();
	jump();

	accelerateUp();

	mVelocity.x = lerp(mVelocityGoal.x, mVelocity.x, timeElapsed * 100);
	mVelocity.y = lerp(mVelocityGoal.y, mVelocity.y, timeElapsed * 100);

	// Updates the player's position
	mSprite.move((mVelocity + mGravity) * timeElapsed);


	// Keeps the player above the bottom, ####TEMPORARY####
	/*if (mSprite.getPosition().y > 660) mSprite.setPosition(mSprite.getPosition().x, 660);
	mSpriteOutline.setPosition(mSprite.getPosition());*/

	accelerateDown();
}

float Player::lerp(float goal, float current, float delta) {
	float difference = goal - current;

	// Interpolates the velocity up from stationary
	if (difference > delta) {
		return current + delta;
	}
	// Interpolates the velocity down to stationary
	if (difference < -delta) {
		return current - delta;
	}

	// Max velocity
	return goal;
}

void Player::jump() {
	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		mClickOnce++;
	}
	else {
		mClickOnce = 0;
	}

	if (mClickOnce == 1 && mNrofJumpsLeft > 0) {
		mNrofJumpsLeft--;
		mGrounded = false;
		mVelocity.y = jumpVelocity;
	}
}

void Player::accelerateUp(){
	// Adds velocity in four directions
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mVelocityGoal.y = mPlayerSpeed * -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mVelocityGoal.y = mPlayerSpeed * 1;
	}*/	

	// Left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mVelocityGoal.x = mPlayerSpeed * -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mVelocityGoal.x = mPlayerSpeed * 1;
	}

}

void Player::accelerateDown(){
	// Resets the velocity to zero
	/*if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mVelocityGoal.y = 0;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mVelocityGoal.y = 0;
	}*/

	// Left and right
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mVelocityGoal.x = 0;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mVelocityGoal.x = 0;
	}
}

void Player::addVector(sf::Vector2f &vector){
	mGravity = vector;
}

void Player::showCoords(){
	//std::cout << "X: " << mSprite.getPosition().x << " Y: " << mSprite.getPosition().y << std::endl;
}

void Player::move(sf::Vector2f &direction) {

	mSprite.move(direction);

	if (direction.y < 0) {
		mVelocity.y = -mGravity.y;
		mGrounded = true;
		mNrofJumpsLeft = 3;
	}
}

void Player::speedModifier() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		mPlayerSpeed = 5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		mPlayerSpeed = 50;
	}
	else {
		mPlayerSpeed = 30;
	}
}