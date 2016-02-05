#include "Worm.h"

static const float ANIFramesPerFrame(0.5);

Worm::Worm(sf::Vector2f pos) :
mCurrentAnimation(Animations::getWormCrawlingLeftANI()),
mIsOnScreen(true),
mSpeed(0.8),
mMaxSpeed(8){
	mSprite.setTexture(*mCurrentAnimation->at(0));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Worm::~Worm(){
}

Entity* Worm::createWorm(sf::Vector2f pos){
	return new Worm(pos);
}

void Worm::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

void Worm::update(){
	Worm::addSpeed();

	Worm::updateCollision();
	Worm::updateState();
	Worm::animate();

	mSprite.move(mVelocity);
}

void Worm::addVector(sf::Vector2f &vector){
	mVelocity += vector;
}

void Worm::entityCollision(Entity* entity, char direction){

}

void Worm::terrainCollision(Terrain* terrain, char direction){
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
			mSprite.move(sf::Vector2f(0, delta - this->getHeight() - 1));
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

void Worm::addSpeed(){
	if (mVelocity.x < mMaxSpeed && mVelocity.x > 0)
		mVelocity.x += mSpeed;
	if (mVelocity.x > -mMaxSpeed && mVelocity.x <= 0)
		mVelocity.x -= mSpeed;
}

void Worm::updateState(){
	if (mVelocity.x > 0){
		mState = Worm::CRAWLINGRIGHT;
		Worm::updateANI();
	}

	if (mVelocity.x < 0){
		mState = Worm::CRAWLINGLEFT;
		Worm::updateANI();
	}
}


void Worm::updateANI(){
	switch (mState){
	case Worm::CRAWLINGLEFT:
		mCurrentAnimation = Animations::getWormCrawlingLeftANI();
		break;
	case Worm::CRAWLINGRIGHT:
		mCurrentAnimation = Animations::getWormCrawlingRightANI();
		break;
	default:
		break;
	}
}

void Worm::updateCollision(){
	if (mCollisionT){
		if (!Worm::currentCollisionT()){
			mCollisionT = false;
		}
	}
	if (mCollisionB){
		if (!Worm::currentCollisionB()){
			mCollisionB = false;
		}
	}
	if (mCollisionL){
		if (!Worm::currentCollisionL()){
			mCollisionL = false;
		}
		else{
			mVelocity.x = mSpeed;
		}
	}
	if (mCollisionR){
		if (!Worm::currentCollisionR()){
			mCollisionR = false;
		}
		else{
			mVelocity.x = -mSpeed;
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

void Worm::animate(){
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

bool Worm::currentCollisionB(){

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

bool Worm::currentCollisionT(){

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

bool Worm::currentCollisionL(){

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

bool Worm::currentCollisionR(){

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





