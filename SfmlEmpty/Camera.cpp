#include "Camera.h"
#include <iostream>


Camera::Camera() :
mMapBounds(0.0f, 0.0f, Toolbox::getResolution().x - Toolbox::getWindowSize().x, Toolbox::getResolution().y - Toolbox::getWindowSize().y),
mIsFullscreen(true),
mEditorCamCenter(Toolbox::getWindowSize().x / 2, Toolbox::getWindowSize().y / 2),
mView(sf::FloatRect(0.f,0.f,1920,1080)){
	// Default view
	mView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

Camera::~Camera(){
}

// Resets the view to display everything within xStart to xStop & yStart to yStop
void Camera::resetCamera(float xStart, float yStart, float xStop, float yStop){
	mView.reset(sf::FloatRect(xStart, yStart, xStop, yStop));
}

void Camera::moveCameraEDITOR(sf::Window &window, sf::Vector2f direction, float speed){
	mView.move(sf::Vector2f(direction.x * speed, direction.y * speed));
	
	//mEditorCamCenter.x += direction.x*speed;
	//mEditorCamCenter.y += direction.y*speed;
	/*sf::Vector2f pos;
	pos.x = mEditorCamCenter.x + direction.x*speed - (window.getPosition().x / 2);
	pos.y = mEditorCamCenter.y + direction.y*speed - (window.getPosition().y / 2);*/

	/*sf::Vector2f pos;
	pos.x = mEditorCamCenter.x + direction.x*speed;
	pos.y = mEditorCamCenter.y + direction.y*speed;*/

	/*if (pos.x < 0)
	pos.x = 0;
	if (pos.y < 0)
	pos.y = 0;
	if (pos.x > mMapBounds.width)
	pos.x = mMapBounds.width;
	if (pos.y > mMapBounds.height)
	pos.y = mMapBounds.height;*/
	/*std::cout << "Pos X: " << pos.x << std::endl
		<< "Pos Y: " << pos.y << std::endl
		<< "windowSize x: " << window.getSize().x << std::endl
		<< "windowSize y: " << window.getSize().y << std::endl << std::endl;
	mView.setCenter(mEditorCamCenter);*/
	
	//mView.reset(sf::FloatRect(pos.x, pos.y, window.getSize().x, window.getSize().y));
}

void Camera::updateCamGAME(sf::Window &window, sf::Vector2f &playerPositon){

	sf::Vector2f focusPoint;
	focusPoint.x = playerPositon.x + 10 - (window.getPosition().x / 2);
	focusPoint.y = playerPositon.y + 10 - (window.getPosition().y / 2);

	if (focusPoint.x < 0)
		focusPoint.x = 0;
	if (focusPoint.y < 0)
		focusPoint.y = 0;
	if (focusPoint.x > mMapBounds.width)
		focusPoint.x = mMapBounds.width;
	if (focusPoint.y > mMapBounds.height)
		focusPoint.y = mMapBounds.height;

	mView.reset(sf::FloatRect(focusPoint.x, focusPoint.y, window.getSize().x, window.getSize().y));
}

void Camera::updateCamEDITOR(sf::Window &window, std::string direction){
	if (direction == "Up")
		moveCameraEDITOR(window, sf::Vector2f(0.f, -1.f), 4.0f);
	else if (direction == "Down"){
		moveCameraEDITOR(window, sf::Vector2f(0.f, 1.f), 4.0f);
	}
	else if (direction == "Right"){
		moveCameraEDITOR(window, sf::Vector2f(1.f, 0.f), 4.0f);
	}
	else if (direction == "Left"){
		moveCameraEDITOR(window, sf::Vector2f(-1.f, 0.f), 4.0f);
	}
	/*sf::Event gEvent;*/
//	while (window.pollEvent(gEvent)){
		/*if (gEvent.type == sf::Event::MouseMoved)
		moveCameraEDITOR(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));*/
	//	if (gEvent.type == sf::Event::KeyPressed){

			/*switch (gEvent.key.code){
			case sf::Keyboard::W:
			moveCameraEDITOR(window,sf::Vector2f(0.f,1.f), 2.0f);
			break;
			case sf::Keyboard::A:
			moveCameraEDITOR(window,sf::Vector2f(-1.f, 0.f), 2.0f);
			break;
			case sf::Keyboard::S:
			moveCameraEDITOR(window,sf::Vector2f(0.f, -1.f), 2.0f);
			break;
			case sf::Keyboard::D:
			moveCameraEDITOR(window,sf::Vector2f(1.f, 0.f), 2.0f);
			break;
			default:
			break;
			}*/
		/*}
	}*/
}