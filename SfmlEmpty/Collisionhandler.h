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
};

