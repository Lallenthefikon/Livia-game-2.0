#include "GameRun.h"


GameRun::GameRun(std::string &mapname):
	
// Initiate singleton classes
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance(&mTerrainHandler, &mEntityHandler))
{
	Toolbox::loadTextures();
	mMapGenerator.loadMap(mapname);
}


GameRun::~GameRun(){
}

GameRun* GameRun::getInstance(std::string &mapname){
	static GameRun gamerun(mapname);
	return &gamerun;
}

void GameRun::update(sf::RenderWindow &window){
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){

		if (gEvent.type == sf::Event::Closed)
			window.close();

	}
	mEntityHandler.updateEntities();
}

void GameRun::render(sf::RenderWindow &window){
	window.clear();
	mEntityHandler.renderEntities(window);
	mTerrainHandler.renderTerrains(window);
	window.display();
}