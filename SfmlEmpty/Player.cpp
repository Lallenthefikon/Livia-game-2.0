#include "Player.h"
#include <iostream>

static float FRIKTION(0.5);
static const float ANIFramesPerFrame(0.5);

Player::Player(sf::Vector2f pos) :
mVelocity(0, 0),
mIsOnScreen(true),
mState(IDLE),

// Animatin stuff
mAnimationIndex(0),
mCurrentAnimation(Animations::getPlayerRunningANI()),
mTimer(1),

// Stats
mJumpSpeed(-32),
mMaxSpeed(15),
mSpeed(1.2){

	mSprite.setTexture(*mCurrentAnimation->at(0));
	mSpriteOffset = sf::Vector2f(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
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
	
	Player::playerInput();
	Player::addFriktion();
	Player::updateCollision();
	Player::updateState();
	Player::animate();

	mSprite.move(mVelocity);

	// Reset temps
	mInput = sf::Vector2f(0, 0);
}

void Player::addVector(sf::Vector2f &vector){
	mVelocity += vector;
}

void Player::entityCollision(Entity* entity, char direction){
	
}

void Player::terrainCollision(Terrain* terrain, char direction){
	float delta;
	switch (terrain->getType())	{
	case Terrain::BLOCK0:
		switch (direction){

		case 't':
			mCollisionT = true;
			delta = mSprite.getPosition().y - terrain->getPos().y;
			mSprite.move(sf::Vector2f(0, terrain->getHeight() - delta + 1));
			mCurrentCollisionT = terrain;
			break;
		case 'b':
			mCollisionB = true;
			delta = terrain->getPos().y - mSprite.getPosition().y;
			mSprite.move(sf::Vector2f(0, delta - this->getHeight()- 1));
			mCurrentCollisionB = terrain;
			break;
		case 'l':
			mCollisionL = true;
			delta = mSprite.getPosition().x - terrain->getPos().x;
			mSprite.move(sf::Vector2f(terrain->getWidth() - delta + 1, 0));
			mCurrentCollisionL = terrain;
			break;
		case 'r':
			mCollisionR = true;
			delta = terrain->getPos().x - mSprite.getPosition().x;
			mSprite.move(sf::Vector2f(delta - this->getWidth(), 0));
			mCurrentCollisionR = terrain;
			break;

		default:
			break;
		}
	default:
		break;
	}
}

// Privates

void Player::playerInput(){

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (mState != JUMPING && mState != FALLING){
			mInput.y += mJumpSpeed;
		}
	}

	// Left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (mVelocity.x > mMaxSpeed * -1)
			mInput.x -= mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (mVelocity.x < mMaxSpeed)
			mInput.x += mSpeed;
	}
	Player::addVector(mInput);
}

void Player::addFriktion(){
	if (mVelocity.x < 0){
		if (mVelocity.x >0){
			mVelocity.x = 0;
		}
		else{
			Player::addVector(sf::Vector2f(FRIKTION, 0));
		}
	}
	if (mVelocity.x > 0){
		if (mVelocity.x < FRIKTION){
			mVelocity.x = 0;
		}
		else{
			Player::addVector(sf::Vector2f(-FRIKTION, 0));
		}
	}
}
	
void Player::updateState(){

	if (mVelocity.x != 0 && mState != JUMPING && mState != RUNNING){
		mState = RUNNING;
		Player::updateANI();
	}

	if (mVelocity.x == 0 && mState != JUMPING && mState != IDLE){
		mState = IDLE;
		Player::updateANI();
	}

	if (mVelocity.y > 0 && mState != FALLING){
		mState = FALLING;
		Player::updateANI();
	}
	if (mVelocity.y < 0 && mState != JUMPING){
		mState = JUMPING;
		Player::updateANI();
	}
}

void Player::updateCollision(){
	if (mCollisionT){
		if (!Player::currentCollisionT()){
			mCollisionT = false;
		}
	}
	if (mCollisionB){
		if (!Player::currentCollisionB()){
			mCollisionB = false;
		}
	}
	if (mCollisionL){
		if (!Player::currentCollisionL()){
			mCollisionL = false;
		}
	}
	if (mCollisionR){
		if (!Player::currentCollisionR()){
			mCollisionR = false;
		}
	}

	if (mCollisionT && mVelocity.y < 0)
		mVelocity.y = 0;
	if (mCollisionB && mVelocity.y > 0)
		mVelocity.y = 0;
	if (mCollisionL && mVelocity.x < 0)
		mVelocity.x = 0;
	if (mCollisionR && mVelocity.x > 0)
		mVelocity.x = 0;
}

void Player::updateANI(){
	switch (mState){

	case JUMPING:
		mCurrentAnimation = Animations::getPlayerJumpingANI();
		break;

	case IDLE:
		mCurrentAnimation = Animations::getPlayerIdleANI();
		break;

	case RUNNING:
		mCurrentAnimation = Animations::getPlayerRunningANI();
		break;

	case FALLING:
		break;

	default:
		break;
	}
	mTimer = 0;
}

void Player::animate(){

	mTimer += ANIFramesPerFrame;
	
	if (mTimer >= 1){
		mAnimationIndex += 1;
		mTimer = 0;
		if (mAnimationIndex >= mCurrentAnimation->size())
			mAnimationIndex = 0;
		if (mCurrentAnimation->size() > 0)
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	}
}

bool Player::currentCollisionB(){
	
	float e0Left = this->getPos().x;
	float e0Right = this->getPos().x + this->getWidth();
	float e0Top = this->getPos().y;
	float e0Bottom = this->getPos().y + this->getHeight();

	float e1Left = mCurrentCollisionB->getPos().x;
	float e1Right = mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth();
	float e1Top = mCurrentCollisionB->getPos().y - 1;
	float e1Bottom = mCurrentCollisionB->getPos().y + mCurrentCollisionB->getHeight() + 1;


	// Has collided if all conditions are met
	if (e0Left <= e1Right &&
		e0Right >= e1Left &&
		e0Top <= e1Bottom &&
		e0Bottom >= e1Top) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::currentCollisionT(){

	float e0Left = this->getPos().x;
	float e0Right = this->getPos().x + this->getWidth();
	float e0Top = this->getPos().y;
	float e0Bottom = this->getPos().y + this->getHeight();

	float e1Left = mCurrentCollisionT->getPos().x;
	float e1Right = mCurrentCollisionT->getPos().x + mCurrentCollisionT->getWidth();
	float e1Top = mCurrentCollisionT->getPos().y - 1;
	float e1Bottom = mCurrentCollisionT->getPos().y + mCurrentCollisionT->getHeight() + 1;


	// Has collided if all conditions are met
	if (e0Left <= e1Right &&
		e0Right >= e1Left &&
		e0Top <= e1Bottom &&
		e0Bottom >= e1Top) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::currentCollisionL(){

	float e0Left = this->getPos().x;
	float e0Right = this->getPos().x + this->getWidth();
	float e0Top = this->getPos().y;
	float e0Bottom = this->getPos().y + this->getHeight();

	float e1Left = mCurrentCollisionL->getPos().x - 1;
	float e1Right = mCurrentCollisionL->getPos().x + mCurrentCollisionL->getWidth() + 1;
	float e1Top = mCurrentCollisionL->getPos().y;
	float e1Bottom = mCurrentCollisionL->getPos().y + mCurrentCollisionL->getHeight();


	// Has collided if all conditions are met
	if (e0Left <= e1Right &&
		e0Right >= e1Left &&
		e0Top <= e1Bottom &&
		e0Bottom >= e1Top) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::currentCollisionR(){

	float e0Left = this->getPos().x;
	float e0Right = this->getPos().x + this->getWidth();
	float e0Top = this->getPos().y;
	float e0Bottom = this->getPos().y + this->getHeight();

	float e1Left = mCurrentCollisionR->getPos().x - 1;
	float e1Right = mCurrentCollisionR->getPos().x + mCurrentCollisionR->getWidth() + 1;
	float e1Top = mCurrentCollisionR->getPos().y;
	float e1Bottom = mCurrentCollisionR->getPos().y + mCurrentCollisionR->getHeight();


	// Has collided if all conditions are met
	if (e0Left <= e1Right &&
		e0Right >= e1Left &&
		e0Top <= e1Bottom &&
		e0Bottom >= e1Top) {
		return true;
	}
	else {
		return false;
	}
}



















//static float timeElapsed = 0.1666666666666667;
//static float jumpVelocity = -300;
//
//Player::Player(sf::Vector2f pos) :
//mPlayerSpeed(30),
//mSpriteOutline(){
//	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::PLAYERTEXTURE), sf::IntRect(0,0,120,140));
//	mSprite.setTexture(mTexture);
//	mSpriteOffset = sf::Vector2f(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
//	mSprite.setPosition(pos - mSpriteOffset);
//	mSpriteOutline.setSize(sf::Vector2f(mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));
//	mSpriteOutline.setPosition(mSprite.getPosition());
//	mSpriteOutline.setFillColor(sf::Color::Red);
//}
//
//
//Player::~Player(){
//}
//
//Entity* Player::createPlayer(sf::Vector2f pos){
//	return new Player(pos);
//}
//
//void Player::render(sf::RenderWindow &window){
//	//window.draw(mSpriteOutline);
//	window.draw(mSprite);
//}
//
//void Player::update(){
//	move();
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
//		showCoords();
//	}
//}
//
//void Player::move() {
//
//	accelerateUp();
//
//	jump();
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
//		mPlayerSpeed = 5;
//	}
//	else {
//		mPlayerSpeed = 30;
//	}
//
//	mVelocity.x = lerp(mVelocityGoal.x, mVelocity.x, timeElapsed * 100);
//	if (!mGrounded) {
//		mVelocity.y = lerp(mVelocityGoal.y, mVelocity.y, timeElapsed * 100);
//	}
//
//	// Updates the player's position
//	mSprite.move((mVelocity + mGravity) * timeElapsed);
//
//	// Keeps the player above the bottom, ####TEMPORARY####
//	/*if (mSprite.getPosition().y > 660) mSprite.setPosition(mSprite.getPosition().x, 660);
//	mSpriteOutline.setPosition(mSprite.getPosition());*/
//
//	accelerateDown();
//
//	
//}
//
//float Player::lerp(float goal, float current, float delta) {
//	float difference = goal - current;
//
//	// Interpolates the velocity up from stationary
//	if (difference > delta) {
//		return current + delta;
//	}
//	// Interpolates the velocity down to stationary
//	if (difference < -delta) {
//		return current - delta;
//	}
//
//	// Max velocity
//	return goal;
//}
//
//void Player::jump() {
//	// Jump
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//		mGrounded = false;
//		mVelocity.y = jumpVelocity;
//	}
//}
//
//void Player::accelerateUp(){
//	// Adds velocity in four directions
//	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//		mVelocityGoal.y = mPlayerSpeed * -1;
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//		mVelocityGoal.y = mPlayerSpeed * 1;
//	}	*/
//
//	// Left and right
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//		mVelocityGoal.x = mPlayerSpeed * -1;
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//		mVelocityGoal.x = mPlayerSpeed * 1;
//	}
//
//}
//
//void Player::accelerateDown(){
//	// Resets the velocity to zero
//	/*if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//		mVelocityGoal.y = 0;
//	}
//	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//		mVelocityGoal.y = 0;
//	}*/
//
//	// Left and right
//	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//		mVelocityGoal.x = 0;
//	}
//	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//		mVelocityGoal.x = 0;
//	}
//}
//
//void Player::addVector(sf::Vector2f &vector){
//	mGravity = vector;
//}
//
//void Player::showCoords(){
//	std::cout << "X: " << mSprite.getPosition().x << " Y: " << mSprite.getPosition().y << std::endl;
//}
//
//void Player::move(sf::Vector2f &direction) {
//
//	mSprite.move(direction);
//
////	if (direction.y > 0) {
////		mSprite.move(direction);
////		/*mSprite.move(direction * mGravity.y * timeElapsed);
////		mSpriteOutline.move(direction * mGravity.y * timeElapsed);*/
////	}
////	
////	if (direction.y < 0) {
////		mSprite.move(direction);
////		/*mGrounded = true;
////		mVelocity.y = -mGravity.y;*/
////		//mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y);
////}
////	
////	if (direction.x < 0 || direction.x > 0) {
////		mSprite.move(direction * mPlayerSpeed * timeElapsed);
////		mSpriteOutline.move(direction * mPlayerSpeed * timeElapsed);
////	}
//}

