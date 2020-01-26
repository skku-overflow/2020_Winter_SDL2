#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER
#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* ren);	

};

#endif