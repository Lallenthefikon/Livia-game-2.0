#pragma once
#include <SFML\Graphics.hpp>
#include "ToolBox.h"
// Ludvig
class Camera
{
public:
	//Toolbox::getWindowSize(), Toolbox::getResolution(), Toolbox::getWindowPos()
	//sf::Vector2f windowSize, sf::Vector2f resolution, sf::Vector2f windowPos
	//sf::Vector2f windowSize, sf::Vector2f resolution
	Camera();
	~Camera();
	void resetCamera(float xStart, float yStart, float xStop, float yStop);
	void updateCamGAME(sf::Window &window, sf::Vector2f &playerPosition);
	void updateCamEDITOR(sf::Window &window, std::string direction);
	bool getIsFullscreen(){ return mIsFullscreen; }
	sf::View getView(){ return mView; }
private:
	sf::View mView;
	sf::FloatRect mMapBounds;
	sf::Vector2f mEditorCamCenter;
	bool mIsFullscreen;

	void moveCameraEDITOR(sf::Window &window, sf::Vector2f direction, float speed);
	void zoomCameraEDITOR();
};