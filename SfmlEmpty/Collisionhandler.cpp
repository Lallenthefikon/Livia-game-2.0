#include "Collisionhandler.h"

Collisionhandler::Collisionhandler(){
}

Collisionhandler::~Collisionhandler(){
}

Collisionhandler& Collisionhandler::getInstance(){
	static Collisionhandler collisionhandler;
	return collisionhandler;
}

void Collisionhandler::checkCollision(Entities &entities, Terrains &terrains){
	collisionBetweenEntities(entities);
	collisionBetweenEntitiesAndTerrains(entities, terrains);
}

void Collisionhandler::collisionBetweenEntities(Entities &entities){
	for (Entities::size_type i = 0; i < entities.size(); i++){
		Entity *e0 = entities[i];
		for (Entities::size_type j = i + 1; j < entities.size(); j++){
			Entity *e1 = entities[j];
			if (e0->isOnScreen() && e1->isOnScreen()) {
				if (hasCollided(e0, e1)) {
					
				}
			}
		}
	}
}

void Collisionhandler::collisionBetweenEntitiesAndTerrains(Entities &entities, Terrains &terrains){
	for (Entities::size_type i = 0; i < entities.size(); i++){
		Entity *e0 = entities[i];
		for (Terrains::size_type j = 0; j < terrains.size(); j++){
			Terrain *e1 = terrains[j];
			if (e0->isOnScreen() && e1->isOnScreen()) {
				if (hasCollided(e0, e1)) {
					
				}
			}
		}
	}
}

bool Collisionhandler::hasCollided(Entity *e0, Entity *e1) {

	float e0Left = e0->getPos().x;
	float e0Right = e0->getPos().x + e0->getWidth();
	float e0Top = e0->getPos().y;
	float e0Bottom = e0->getPos().y + e0->getHeight();

	float e1Left = e1->getPos().x;
	float e1Right = e1->getPos().x + e1->getWidth();
	float e1Top = e1->getPos().y;
	float e1Bottom = e1->getPos().y + e1->getHeight();

	// Has collided if all conditions are met
	if (e0Left < e1Right &&
		e0Right > e1Left &&
		e0Top < e1Bottom &&
		e0Bottom > e1Top) {
		return true;
	}
	else {
		return false;
	}
}

bool Collisionhandler::hasCollided(Entity *e0, Terrain *e1) {

	float e0Left = e0->getPos().x;
	float e0Right = e0->getPos().x + e0->getWidth();
	float e0Top = e0->getPos().y;
	float e0Bottom = e0->getPos().y + e0->getHeight();

	float e1Left = e1->getPos().x;
	float e1Right = e1->getPos().x + e1->getWidth();
	float e1Top = e1->getPos().y;
	float e1Bottom = e1->getPos().y + e1->getHeight();

	// Has collided if all conditions are met
	if (e0Left < e1Right && e0Right > e1Left &&
		e0Top < e1Bottom && e0Bottom > e1Top) {
		return true;
	}
	else {
		return false;
	}
}