#include "GameLoop.h"
#include <iostream>


GameLoop::GameLoop():
mCurrentMap("MMap0.txt"),
mWindow(sf::VideoMode(640, 480), "SFML Application"){
	mWindow.setVerticalSyncEnabled(true);
	
}


GameLoop::~GameLoop(){
}

void GameLoop::run(){

	//mCurrentState = GameRun::getInstance(mCurrentMap);
	mCurrentState = MapEditor::getInstance();

	shape.setRadius(80.f);
	shape.setPosition((mWindow.getSize().x / 2) - shape.getRadius(), (mWindow.getSize().y / 2) - shape.getRadius());
	shape.setFillColor(sf::Color::Red);
	mWindow.setKeyRepeatEnabled(false);

	

	sf::Clock clock;


	// Loop
	while (mWindow.isOpen()){

		sf::Event gEvent;
		while (mWindow.pollEvent(gEvent)){

			if (gEvent.type == sf::Event::Closed)
				mWindow.close();
			update(gEvent);
		}

		render();
		calcTimeElapsedAndFPS(clock);
	}
}

void GameLoop::update(sf::Event &gEvent){
	mCurrentState->update(gEvent, mWindow);
}

void GameLoop::render(){
	//mWindow.clear();
	
	mCurrentState->render(mWindow);
	
	mWindow.draw(shape);
	//mWindow.display();	
}

void GameLoop::calcTimeElapsedAndFPS(sf::Clock &clock){
	mTimeElapsed = clock.restart().asMilliseconds();
	FPS = 1000.f / mTimeElapsed;
}