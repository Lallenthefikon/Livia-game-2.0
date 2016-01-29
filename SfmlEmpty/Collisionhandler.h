#pragma once

#include "Entity.h"
#include "Terrain.h"

class Collisionhandler{
public:
	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;
	static Collisionhandler& getInstance();
	~Collisionhandler();
	void checkCollision(Entities &entities, Terrains &terrains);
private:
	Collisionhandler();
	void collisionBetweenEntities(Entities &entities);
	void collisionBetweenEntitiesAndTerrains(Entities &entities, Terrains &terrains);
	bool hasCollided(Entity *e0, Entity *e1);
	bool hasCollided(Entity *e0, Terrain *e1);
	void collisionDirection(Entity *e0, Entity *e1);
	void collisionDirection(Entity *e0, Terrain *e1);
};

