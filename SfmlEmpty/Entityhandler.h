#pragma once

#include "Entity.h"
#include <vector>

class Entityhandler{
public:
	typedef std::vector<Entity*> Entities;
	static Entityhandler& getInstance();
	void addEntity(Entity* entity);
	void renderEntities(sf::RenderWindow &window);
	void updateEntities();
	Entities& getEntities(){ return mEntities; }
	void addVector();
private:
	Entityhandler();
	~Entityhandler();
	Entities mEntities;
	sf::Vector2f mGravity;
};
