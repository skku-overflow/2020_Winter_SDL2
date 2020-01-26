#include "TextureManager.h"
#include "GameObject.h"

/*
	Defining the constructor of the "GameObject" Class
	[[[Creating an object]]]
*/
GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int xi, int yi) {
	
	// Assign a new renderer, texture for the newly created GameObject instance
	renderer = ren;
	objTexture = TextureManager::LoadTexture(texturesheet, ren);

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

	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}