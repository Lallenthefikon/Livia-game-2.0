#include "MapEditor.h"
#include <iostream>
#include <fstream>
#include <sstream>

MapEditor::MapEditor(std::string &mapName):
mInsertType(BLOCK0),
mCurrentMap(mapName),
mMaploader(MapEditMaploader::getInstance()){
	Toolbox::loadTextures();
	MapEditor::loadMap();
}

MapEditor::~MapEditor(){
}

MapEditor* MapEditor::getInstance(std::string &mapName){
	static MapEditor mapeditor(mapName);
	return &mapeditor;
}

void MapEditor::update(sf::RenderWindow &window){
	
	// Events
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){

		if (gEvent.type == sf::Event::Closed)
			window.close();

		if (gEvent.type == sf::Event::MouseButtonPressed){

			int xPos = sf::Mouse::getPosition(window).x;
			int yPos = sf::Mouse::getPosition(window).y;

			switch (gEvent.mouseButton.button){

			case sf::Mouse::Left:
				MapEditor::insertObject(sf::Vector2f(xPos, yPos));
				break;

				// Not done
			case sf::Mouse::Right:
				break;

			case sf::Mouse::Middle:
				MapEditor::changeInsertType();
				break;

			default:
				break;
			}
		}

		if (gEvent.type == sf::Event::KeyPressed){
			switch (gEvent.key.code){
			case sf::Keyboard::S:
				MapEditor::saveMap();
				break;

			default:
				break;
			}
		}
	}
}

void MapEditor::render(sf::RenderWindow &window){
	window.clear();

	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		mTerrains[i]->render(window);
	}

	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->render(window);
	}

	window.display();
}

void MapEditor::createBlock0(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createBlock0(mousePos));
}

void MapEditor::createPlayer(sf::Vector2f mousePos){
	bool playerFound(false);
	
	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		if (mEntities[i]->getType() == Entity::PLAYER){
			delete mEntities[i];
			mEntities[i] = Factory::createPlayer(mousePos);
			playerFound = true;
			break;
		}
	}
	if (!playerFound)
		mEntities.push_back(Factory::createPlayer(mousePos));
	
}

void MapEditor::createWorm(sf::Vector2f mousePos){
	mEntities.push_back(Factory::createWorm(mousePos));
}

void MapEditor::loadMap(){
	mCurrentMap[15] = 'E';
	mEntities = mMaploader.getEntities(mCurrentMap);

	mCurrentMap[15] = 'T';
	mTerrains = mMaploader.getTerrain(mCurrentMap);

	mCurrentMap[15] = 'm';

	mMaploader.clear();
}

void MapEditor::clearMap(){
	MapEditor::internalClear();
}


// Privates

void MapEditor::insertObject(sf::Vector2f mousePos) {
	switch (mInsertType){
	case BLOCK0:
		MapEditor::createBlock0(mousePos);
		break;
	case PLAYER:
		MapEditor::createPlayer(mousePos);
		break;
	case WORM:
		MapEditor::createWorm(mousePos);
		break;
	default:
		break;
	}
}

void MapEditor::changeInsertType(){
	switch (mInsertType){
	case BLOCK0:
		mInsertType = PLAYER;
		break;
	case PLAYER:
		mInsertType = WORM;
		break;
	case WORM:
		mInsertType = BLOCK0;
		break;
	default:
		break;
	}
}

void MapEditor::saveMap(){

	mCurrentMap[15] = 'T';
	MapEditor::writeTerrainToFile(mCurrentMap);

	mCurrentMap[15] = 'E';
	MapEditor::writeEntityToFile(mCurrentMap);

	mCurrentMap[15] = 'm';

}

void MapEditor::writeTerrainToFile(std::string filename){

	std::string posString;
	std::string output;
	std::ofstream terrainfile(filename);

	if (terrainfile.is_open()){
		for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
			terrainfile << std::endl;
			
			// Inserts typename into output followed by '-'
			switch (mTerrains[i]->getType()){
			case Terrain::BLOCK0:
				output.push_back('B');
				output.push_back('0');
				break;

			default:
				break;

			}
			output.push_back('-');

			// Inserts xpos into output followed by a ','
			posString = MapEditor::floatToString(mTerrains[i]->getPos().x + mTerrains[i]->getOffset().x);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++){
				output.push_back(posString[iS]);
			}
			output.push_back(',');

			// Inserts ypos into output
			posString = MapEditor::floatToString(mTerrains[i]->getPos().y + mTerrains[i]->getOffset().y);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++){
				output.push_back(posString[iS]);
			}

			// Writes output into file
			terrainfile << output;
			//

			output.clear();
			posString.clear();
		}
	}
	terrainfile.close();
}

void MapEditor::writeEntityToFile(std::string filename){

	std::string posString;
	std::string output;
	std::ofstream entityFile(filename);

	if (entityFile.is_open()){
		for (Entities::size_type i = 0; i < mEntities.size(); i++){

			// Inserts typename into output followed by '-'
			switch (mEntities[i]->getType()){
			case Entity::PLAYER:
				output.push_back('P');
				output.push_back('0');
				break;

			case Entity::WORM:
				output.push_back('W');
				output.push_back('0');
				break;

			default:
				break;
			}
			output.push_back('-');

			// Inserts xpos into output followed by a ','
			posString = MapEditor::floatToString(mEntities[i]->getPos().x + mEntities[i]->getOffset().x);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++){
				output.push_back(posString[iS]);
			}
			output.push_back(',');

			// Inserts ypos into output
			posString = MapEditor::floatToString(mEntities[i]->getPos().y + mEntities[i]->getOffset().x);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++){
				output.push_back(posString[iS]);
			}

			// Writes output into file
			entityFile << output << std::endl;
			//

			output.clear();
			posString.clear();
		}
	}
	entityFile.close();
}

void MapEditor::internalClear(){
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}

	while (!mTerrains.empty()){
		delete mTerrains.back();
		mTerrains.pop_back();
	}
}

std::string MapEditor::floatToString(float f){
	std::ostringstream ss;
	ss << f;
	std::string pos(ss.str());
	return pos;
}