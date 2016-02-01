#pragma once

#include <SFML\Graphics.hpp>

struct Toolbox{
	enum TEXTUREKEY { WORMTEXTURE, BLOCK0TEXTURE, PLAYERTEXTURE, TILETEXTURE };
	static Toolbox& getInstance();
	static void loadTextures();
	static sf::Texture& getTexture(TEXTUREKEY textureKey);
	// Camera Edit
	static void copyScreenInfo(sf::RenderWindow &window, sf::VideoMode &videoMode);
	static sf::Vector2f getWindowSize();
	static sf::Vector2f getResolution();
	static sf::Vector2f getWindowPos();
	//static void copyPlayerInfo(sf::Sprite &playerSprite);
};

