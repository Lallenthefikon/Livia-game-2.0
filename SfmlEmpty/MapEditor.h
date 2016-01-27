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

	static MapEditor* getInstance(std::string mapName);

	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);

	void createPlayer(sf::Vector2f mousePos);
	void createBlock0(sf::Vector2f mousePos);
	void createWorm(sf::Vector2f mousePos);

private:
	MapEditor(std::string mapName);
	~MapEditor();
	void insertObjekt(sf::Vector2f mousePos);
	void changeInsertType();

	

	void saveMap();
	void writeTerrainToFile(std::string filename);
	void writeEntityToFile(std::string filename);

	std::string floatToString(float f);

	INSERTTYPE mInsertType;
	std::string mMapname;

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;

	Entities mEntities;
	Terrains mTerrains;

};

