#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

using namespace std;

class ColliderComponent;

class Game {
public:

	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };
	
	static void AddTile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static vector<ColliderComponent*> colliders;

private:
	
	bool isRunning = false;
	int cnt = 0;
	SDL_Window* window;

};

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);//, SDL_Renderer* ren);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};