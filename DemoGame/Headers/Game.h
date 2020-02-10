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

	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };

	static void AddTile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static vector<ColliderComponent*> colliders;

	void monitoring();

private:
	int cnt=0;
	bool isRunning;
	SDL_Window* window;
	// SDL_Renderer* renderer;


};
