#include "Block0.h"

Block0::Block0(sf::Vector2f pos){
	mSprite.setTexture(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Block0::~Block0(){
}

Terrain* Block0::createBlock0(sf::Vector2f pos){
	return new Block0(pos);
}

void Block0::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

void Block0::update(){

}
