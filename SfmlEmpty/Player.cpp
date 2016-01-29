#include "Player.h"
#include <iostream>

static float timeElapsed = 0.1666666666666667;
static float jumpVelocity = -300;

Player::Player(sf::Vector2f pos) :
mPlayerSpeed(30),
mSpriteOffset(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2){
	mSprite.setTexture(Toolbox::getTexture(Toolbox::PLAYERTEXTURE));
	mSprite.setPosition(pos - mSpriteOffset);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
		showCoords();
	}
}

void Player::move() {

	accelerateUp();

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) mVelocity.y = jumpVelocity;

	mVelocity.x = lerp(mVelocityGoal.x, mVelocity.x, timeElapsed * 100);
	mVelocity.y = lerp(mVelocityGoal.y, mVelocity.y, timeElapsed * 100);

	// Updates the player's position

	mSprite.move((mVelocity + mGravity) * timeElapsed);

	// Keeps the player above the bottom, ####TEMPORARY####
	if (mSprite.getPosition().y > 360) mSprite.setPosition(mSprite.getPosition().x, 360);

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

void Player::accelerateUp(){
	// Adds velocity in four directions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mVelocityGoal.y = mPlayerSpeed * -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mVelocityGoal.y = mPlayerSpeed * 1;
	}
	// Left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mVelocityGoal.x = mPlayerSpeed * -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mVelocityGoal.x = mPlayerSpeed * 1;
	}
}

void Player::accelerateDown(){
	// Resets the velocity to zero
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mVelocityGoal.y = 0;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mVelocityGoal.y = 0;
	}
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
	std::cout << "X: " << mSprite.getPosition().x << " Y: " << mSprite.getPosition().y << std::endl;
}

void Player::collided(std::string &direction){

}

void Player::correctPosition(sf::Vector2f &vector){
	mVelocity = mPlayerSpeed * vector;
}