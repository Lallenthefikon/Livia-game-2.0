#pragma once
#include "GameState.h"
#include <vector>
#include "Factory.h"
#include "Entity.h"
#include "Terrain.h"
#include "Toolbox.h"

class MapEditor : public GameState
{
public:
	enum INSERTTYPE{BLOCK0,
	PLAYER,
	WORM};
	static MapEditor* getInstance();
	virtual void update(sf::Event &gEvent, sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
private:
	MapEditor();
	~MapEditor();
	void insertObjekt(sf::Vector2f mousePos);

	void createPlayer(sf::Vector2f mousePos);
	void createBlock0(sf::Vector2f mousePos);
	void createWorm(sf::Vector2f mousePos);

	INSERTTYPE mInsertType;

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;

	Entities mEntities;
	Terrains mTerrains;
};

