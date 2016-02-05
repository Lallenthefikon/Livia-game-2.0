#include "GameRun.h"

GameRun::GameRun(std::string &mapname):
	
// Initiate singleton classes
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance(mWorld)),
mCollisionHandler(Collisionhandler::getInstance()),
mCurrentMap(mapname),
mCamera(),
mGravity(0, 9.8){
	mWorld = new b2World(mGravity);
	mWorld->SetGravity(mGravity);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(3, 3);

	b2Body* dynamicBody = mWorld->CreateBody(&bodyDef);
	
	b2PolygonShape boxShape;
	boxShape.SetAsBox(1, 1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);

	mWorld->DrawDebugData();

	Toolbox::loadTextures();
	mMapGenerator.loadMap(mapname);
}

GameRun::~GameRun(){
	delete mWorld;
}

GameRun* GameRun::getInstance(std::string &mapname){
	static GameRun gamerun(mapname);
	return &gamerun;
}

void GameRun::update(sf::RenderWindow &window){
	mWorld->Step(timeStep, velocityIterations, positionIterations);
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){

		if (gEvent.type == sf::Event::Closed)
			window.close();

	}
	mEntityHandler.updateEntities();
	mTerrainHandler.updateTerrains();
	mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
	mCamera.updateCamGAME(window);
	window.setView(mCamera.getView());
}

void GameRun::render(sf::RenderWindow &window){
	window.clear();
	mTerrainHandler.renderTerrains(window);
	mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);
	window.display();
}

void GameRun::loadMap(){
	mMapGenerator.loadMap(mCurrentMap);
}
