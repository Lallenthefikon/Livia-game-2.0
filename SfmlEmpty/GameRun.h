#pragma once

#include "GameState.h"
#include "Entityhandler.h"
#include "Terrainhandler.h"
#include "Collisionhandler.h"
#include "MapGenerator.h"
#include "Toolbox.h"
#include "Camera.h"

class GameRun : public GameState{
public:
	static GameRun* getInstance(std::string &mapname);
	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
	virtual void loadMap();
	virtual void setCurrentMap(std::string &mapname){ mCurrentMap = mapname; }
private:
	GameRun(std::string &mapname);
	~GameRun();

	Entityhandler& mEntityHandler;
	Terrainhandler& mTerrainHandler;
	MapGenerator& mMapGenerator;
	Collisionhandler& mCollisionHandler;

	std::string mCurrentMap;

	Camera mCamera;
	b2Vec2 mGravity;
	b2World* mWorld;

	float32 timeStep = 1.0f / 60.f;
	int32 velocityIterations = 10;
	int32 positionIterations = 8;

};

