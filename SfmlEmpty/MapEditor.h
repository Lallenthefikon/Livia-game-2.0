#pragma once

#include "GameState.h"
#include <vector>
#include "Factory.h"
#include "Entity.h"
#include "Terrain.h"
#include "Toolbox.h"
#include "MapEditMaploader.h"

class MapEditor : public GameState{
public:

	enum INSERTTYPE{BLOCK0,
	PLAYER,
	WORM};

	static MapEditor* getInstance(std::string &mapName);

	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);

	void createPlayer(sf::Vector2f mousePos);
	void createBlock0(sf::Vector2f mousePos);
	void createWorm(sf::Vector2f mousePos);

	virtual void setCurrentMap(std::string &mapname){ mCurrentMap = mapname; }
	virtual void loadMap();

	void clearMap();

private:
	MapEditor(std::string &mapName);
	~MapEditor();

	void insertObject(sf::Vector2f mousePos);
	void changeInsertType();

	void saveMap();
	void writeTerrainToFile(std::string filename);
	void writeEntityToFile(std::string filename);
	void internalClear();

	std::string floatToString(float f);

	MapEditMaploader &mMaploader;

	INSERTTYPE mInsertType;
	std::string mCurrentMap;

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;

	Entities mEntities;
	Terrains mTerrains;

};

