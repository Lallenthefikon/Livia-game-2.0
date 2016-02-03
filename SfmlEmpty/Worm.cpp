#include "Worm.h"

Worm::Worm(sf::Vector2f pos){
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::WORMTEXTURE));
	mSprite.setTexture(mTexture);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
	mSpriteOutline.setSize(sf::Vector2f(mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));
	mSpriteOutline.setPosition(mSprite.getPosition());
	mSpriteOutline.setFillColor(sf::Color::Cyan);
}

Worm::~Worm(){
}

Entity* Worm::createWorm(sf::Vector2f pos){
	return new Worm(pos);
}

void Worm::render(sf::RenderWindow &window){
	window.draw(mSpriteOutline);
	window.draw(mSprite);
}

void Worm::update(){

}

void Worm::addVector(sf::Vector2f &vector){

}

void Worm::move(sf::Vector2f &direction) {

}