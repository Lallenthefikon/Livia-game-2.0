#include "Block0.h"

Block0::Block0(sf::Vector2f pos) :
mPosition(pos){
	mSprite.setTexture(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
	sf::Vector2f spriteOffset(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(mPosition - spriteOffset);
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