#include "MapEditor.h"
#include <iostream>


MapEditor::MapEditor():
mInsertType(BLOCK0){
	Toolbox::loadTextures();
}


MapEditor::~MapEditor(){
}

MapEditor* MapEditor::getInstance(){
	static MapEditor mapeditor;
	return &mapeditor;
}

void MapEditor::update(sf::Event &gEvent, sf::RenderWindow &window){
	
	if (gEvent.type == sf::Event::MouseButtonPressed && gEvent.mouseButton.button == sf::Mouse::Left){
		std::cout << "X pos: " << sf::Mouse::getPosition(window).x << std::endl
			<< "Y pos: " << sf::Mouse::getPosition(window).y << std::endl;
		int xPos = sf::Mouse::getPosition(window).x;
		int yPos = sf::Mouse::getPosition(window).y;
		MapEditor::insertObjekt(sf::Vector2f(xPos, yPos));
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

void MapEditor::insertObjekt(sf::Vector2f mousePos){
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

void MapEditor::createBlock0(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createBlock0(mousePos));
}

void MapEditor::createPlayer(sf::Vector2f mousePos){
	/*for (Entities::size_type i = 0; i < mEntities.size(); i++){
		if (mEntities[i]->getType() == Entity::PLAYER){
			delete mEntities[i];
			mEntities.erase[i];
		}
	}*/
	mEntities.push_back(Factory::createPlayer(mousePos));
}

void MapEditor::createWorm(sf::Vector2f mousePos){
	mEntities.push_back(Factory::createWorm(mousePos));
}