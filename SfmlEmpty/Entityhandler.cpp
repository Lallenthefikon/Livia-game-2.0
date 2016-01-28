#include "Entityhandler.h"

Entityhandler::Entityhandler():
mGravity(sf::Vector2f(0, 150)){
}

Entityhandler::~Entityhandler(){
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
}

Entityhandler& Entityhandler::getInstance(){
	static Entityhandler entityhandler;
	return entityhandler;
}

void Entityhandler::renderEntities(sf::RenderWindow &window){
	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->render(window);
	}
}

void Entityhandler::updateEntities(){
	addVector();
	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->update();
	}
}

void Entityhandler::addEntity(Entity* entity){
	mEntities.push_back(entity);
}

void Entityhandler::addVector(){
	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->addVector(mGravity);
	}
}