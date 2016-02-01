#include "Toolbox.h"

// Textures
static sf::Texture mWormtexture;
static sf::Texture mBlock0texture;
static sf::Texture mPlayertexture;

static sf::Texture mTileTexture;
static sf::Texture mEditorMenyTexture;

Toolbox& Toolbox::getInstance(){
	static Toolbox toolbox;
	return toolbox;
}

void Toolbox::loadTextures(){
	mWormtexture.loadFromFile("resources/images/Mask.png");
	mBlock0texture.loadFromFile("resources/images/Block0.png");
	mPlayertexture.loadFromFile("resources/images/Livia test run_00022.png");

	mTileTexture.loadFromFile("resources/images/Tile.png");
	mEditorMenyTexture.loadFromFile("resources/images/EditorMeny.png");
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

	case TILETEXTURE:
		return mTileTexture;
		break;

	case EDITORMENY:
		return mEditorMenyTexture;
		break;

	default:
		break;
	}
}
