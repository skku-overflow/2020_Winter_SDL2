#include "TextureManager.h"
#include "GameObject.h"

/*
	Defining the constructor of the "GameObject" Class
	[[[Creating an object]]]
*/
GameObject::GameObject(const char* texturesheet, int xi, int yi) {
	
	// Assign a new renderer, texture for the newly created GameObject instance
	// renderer = ren;				// Not needed : renderer of Game class
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = xi;
	ypos = yi;
}

/*
	[[[Movement, Behavior of an object]]]
*/
void GameObject::update() {

	xpos++;
	ypos++;

	// Rect { x, y, w, h }
	srcRect = { 0,0, 400, 400 };
	destRect = { xpos, ypos, 50,50 };
}

/*
	[[[Render the texture of an object]]]
*/
void GameObject::render() {

	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}