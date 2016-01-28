#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop():
mCurrentMap("resources/maps/mMap0.txt"),
mWindow(sf::VideoMode(640, 480), "SFML Application"){
	mWindow.setVerticalSyncEnabled(true);
	updateState();
}

GameLoop::~GameLoop(){
}

void GameLoop::switchState(){
	if (!gameRunning){
		gameRunning = true;
		mapEditing = false;
		return;
	}
	else if (!mapEditing){
		mapEditing = true;
		gameRunning = false;
	}
}

void GameLoop::updateState(){
	if (gameRunning){
		mCurrentState = GameRun::getInstance(mCurrentMap);
	}
	else if (mapEditing){
		mCurrentState = MapEditor::getInstance(mCurrentMap);
		MapEditMaploader::getInstance(mCurrentMap).loadMap(mCurrentMap);
	}
}

void GameLoop::manualStateChange(int &i){
	// Switches between the different states
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
		i++;
		//std::cout << i << std::endl;
	}
	else i = 0;

	// Makes sure button acts as if pressed once
	if (i == 1){
		switchState();
		updateState();
	}
}

void GameLoop::run(){
	
	mWindow.setKeyRepeatEnabled(false);

	int clickOnce = 0;

	sf::Clock clock;

	// Loop
	while (mWindow.isOpen()){
		manualStateChange(clickOnce);
		update();
		render();
		calcTimeElapsedAndFPS(clock);
	}
}

void GameLoop::update(){
	mCurrentState->update(mWindow);
}

void GameLoop::render(){
	mCurrentState->render(mWindow);	
}

void GameLoop::calcTimeElapsedAndFPS(sf::Clock &clock){
	mTimeElapsed = clock.restart().asMilliseconds();
	FPS = 1000.f / mTimeElapsed;
}