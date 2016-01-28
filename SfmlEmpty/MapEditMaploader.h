#pragma once

#include "MapEditor.h"



class MapEditMaploader{
public:

	static MapEditMaploader& getInstance(std::string &mapname);
	void loadMap(std::string &mapname);

private:
	MapEditMaploader(std::string &mapname);
	~MapEditMaploader();

	void readTerrainfile(std::string &mapname);
	void readEntityfile(std::string &mapname);

	void createBlock0(sf::Vector2f &pos);
	void createPlayer(sf::Vector2f &pos);
	void createWorm(sf::Vector2f &pos);

	sf::Vector2f readPosition(std::string line);

	MapEditor *mMapEditor;
};

