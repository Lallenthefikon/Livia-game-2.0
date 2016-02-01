#pragma once

#include <SFML\Graphics.hpp>

struct Toolbox{
	enum TEXTUREKEY { WORMTEXTURE, BLOCK0TEXTURE, PLAYERTEXTURE, TILETEXTURE, EDITORMENY };
	static Toolbox& getInstance();
	static void loadTextures();
	static sf::Texture& getTexture(TEXTUREKEY textureKey);
};

