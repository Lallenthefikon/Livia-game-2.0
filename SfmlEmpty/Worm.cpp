#include "Worm.h"

Worm::Worm(sf::Vector2f pos){
	mSprite.setTexture(Toolbox::getTexture(Toolbox::WORMTEXTURE));
	mSprite.setPosition(pos);
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

}

void Worm::addVector(sf::Vector2f &vector){

}

void Worm::collided(std::string &direction) {

}