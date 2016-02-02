#include "MapEditor.h"
#include <iostream>
#include <fstream>
#include <sstream>

MapEditor::MapEditor(std::string &mapName) :
mMapDimensionsTiles(50, 50),
mTileDimensions(70.f, 70.f),
mInsertType(MapEditorMeny::BLOCK0),
mCurrentMap(mapName),
mMaploader(MapEditMaploader::getInstance()),
mMeny(MapEditorMeny::getInstance()),
mCamera(){

	Toolbox::loadTextures();
	MapEditor::loadMap();
	MapEditor::createGrid();
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


			if (mMeny.menyClicked(sf::Mouse::getPosition(window))){
				MapEditor::updateInsertType();
			}

			else{
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
				sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
				int i;

				sf::Sprite clickedTile;
				switch (gEvent.mouseButton.button){

				case sf::Mouse::Left:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
						MapEditor::insertObject(sf::Vector2f(coord_pos.x, coord_pos.y));
					}
					else{
						sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
						sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
						clickedTile = determineSelectedTileInGrid(coord_pos, &mGrid);
						// Offset applied in all tiles, counteroffset needed here to match grid.
						MapEditor::insertObject(sf::Vector2f(
							clickedTile.getPosition().x + clickedTile.getLocalBounds().width / 2
							, clickedTile.getPosition().y + clickedTile.getLocalBounds().height / 2));
					}
					break;


				case sf::Mouse::Right:
					for (i = mEntities.size() - 1; i > -1; i--){
						if (MapEditor::isSpriteClicked(mEntities[i]->getSprite(), &coord_pos)){
							MapEditor::eraseEntity(i);
							break;
						}
					}
					for (i = mTerrains.size() - 1; i > -1; i--){
						if (MapEditor::isSpriteClicked(mTerrains[i]->getSprite(), &coord_pos)){
							MapEditor::eraseTerrain(i);
							break;
						}
					}
						break;

				case sf::Mouse::Middle:
					MapEditor::changeInsertType();
					break;
				default:
					break;
					}
				}
			}
		if (gEvent.type == sf::Event::MouseWheelMoved){
			mCamera.zoomCameraEDITOR(gEvent);
		}

		if (gEvent.type == sf::Event::KeyPressed){
			switch (gEvent.key.code){
			case sf::Keyboard::S:
				MapEditor::saveMap();
				break;
			case sf::Keyboard::Delete:
				MapEditor::internalClear();
				break;
			default:
				break;
			}
		}
		}

		

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		mCamera.updateCamEDITOR(window, "Up");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		mCamera.updateCamEDITOR(window, "Down");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		mCamera.updateCamEDITOR(window, "Right");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		mCamera.updateCamEDITOR(window, "Left");

	window.setView(mCamera.getView());
}

void MapEditor::render(sf::RenderWindow &window){
	window.clear();

	for (size_t i = 0; i < mGrid.size(); i++){
		window.draw(mGrid[i]);
	}

	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		mTerrains[i]->render(window);
	}

	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->render(window);
	}
	mMeny.render(window);

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
	case MapEditorMeny::BLOCK0:
		MapEditor::createBlock0(mousePos);
		break;
	case MapEditorMeny::PLAYER:
		MapEditor::createPlayer(mousePos);
		break;
	case MapEditorMeny::WORM:
		MapEditor::createWorm(mousePos);
		break;
	default:
		break;
	}
}

void MapEditor::eraseEntity(int index){
	delete mEntities[index];
	mEntities.erase(mEntities.begin() + index);
}

void MapEditor::eraseTerrain(int index){
	delete mTerrains[index];
	mTerrains.erase(mTerrains.begin() + index);
}

void MapEditor::changeInsertType(){
	switch (mInsertType){
	case MapEditorMeny::BLOCK0:
		mInsertType = MapEditorMeny::PLAYER;
		break;
	case MapEditorMeny::PLAYER:
		mInsertType = MapEditorMeny::WORM;
		break;
	case MapEditorMeny::WORM:
		mInsertType = MapEditorMeny::BLOCK0;
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

void MapEditor::createGrid(){
	sf::Vector2f lastTilePos(-mTileDimensions.x, -mTileDimensions.y);
	//std::vector<sf::Sprite> tiles;

	for (size_t i = 0; i < mMapDimensionsTiles.x; i++){
		sf::Vector2f tilePos(0, 0);
		tilePos.x = lastTilePos.x;
		tilePos.x += mTileDimensions.x;

		sf::Sprite xTile;
		xTile.setTexture(Toolbox::getTexture(Toolbox::TILETEXTURE));
		xTile.setPosition(tilePos);

		mGrid.push_back(xTile);
		//std::cout << "X: " << xTile.getPosition().x << std::endl << "Y: " << xTile.getPosition().y << std::endl << std::endl;

		for (size_t j = 0; j < mMapDimensionsTiles.y - 1; j++){
			tilePos.y += mTileDimensions.y;

			sf::Sprite yTile;
			yTile.setTexture(Toolbox::getTexture(Toolbox::TILETEXTURE));
			yTile.setPosition(tilePos);
			mGrid.push_back(yTile);

			lastTilePos = tilePos;
			//std::cout << "X: " << yTile.getPosition().x << std::endl << "Y: " << yTile.getPosition().y << std::endl << std::endl;
		}
		lastTilePos.y = 0;
		lastTilePos.x = tilePos.x;
	}
	std::cout << "Tiles created: " << mGrid.size() << std::endl;
}


sf::Sprite MapEditor::determineSelectedTileInGrid(sf::Vector2f position, std::vector<sf::Sprite> *grid){
	for (size_t i = 0; i < grid->size(); i++){
		if (isSpriteClicked(grid->at(i), &position)){
			return grid->at(i);
		}
	}
}


bool MapEditor::isSpriteClicked(sf::Sprite& spr, sf::Vector2f *mousePos){
	return mousePos->x > spr.getPosition().x
		&& mousePos->x < spr.getPosition().x + spr.getLocalBounds().width
		&& mousePos->y > spr.getPosition().y
		&& mousePos->y < spr.getPosition().y + spr.getLocalBounds().height;
}

void MapEditor::updateInsertType(){
	mInsertType = mMeny.getInsertType();
}
