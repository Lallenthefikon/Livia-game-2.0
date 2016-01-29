#include "Toolbox.h"

// Textures
static sf::Texture mWormtexture;
static sf::Texture mBlock0texture;
static sf::Texture mPlayertexture;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(){
	mWormtexture.loadFromFile("resources/images/Mask.png");
	mBlock0texture.loadFromFile("resources/images/Block0.png");
	mPlayertexture.loadFromFile("resources/images/Livia test run_00022.png");
}

sf::Texture& Toolbox::getTexture(TEXTUREKEY textureKey){
	switch (textureKey){

	case WORMTEXTURE:
		return mWormtexture;
		break;

	case BLOCK0TEXTURE:
		return mBlock0texture;
		break;

	case PLAYERTEXTURE:
		return mPlayertexture;
		break;

	default:
		break;
	}
}
