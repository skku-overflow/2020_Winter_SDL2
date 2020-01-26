#ifndef GAMEOBJECT
#define GAMEOBJECT
#include "Game.h"

/*
	A class for in-game objects:
	Every objects created with this class will have its own configs, movements, etc.
*/
class GameObject {

public:
	GameObject(const char* texturesheet, SDL_Renderer* ren, int xi, int yi);
	~GameObject();

	void update();
	void render();
	

private:

	int xpos, ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;


};

#endif