#include "Block0.h"

Block0::Block0(sf::Vector2f pos, char type){
	Block0::setTexture(type);
	mSprite.setTexture(mTexture);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Block0::~Block0(){
}

Terrain* Block0::createBlock0(sf::Vector2f pos, char type){
	return new Block0(pos, type);
}

void Block0::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

void Block0::update(){

}

void Block0::setTexture(char type){
	switch (type){
	case 'a':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'b':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'c':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'd':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'e':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));	
		break;

	case 'f':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'g':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'h':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'i':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'j':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'k':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'l':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'm':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'n':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'o':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	case 'p':
		mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE));
		break;

	default:
		break;
	}
}
