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

	static void AddTile(int srcX, int srcY, int xpos, int ypos);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static vector<ColliderComponent*> colliders;

	static bool isRunning;
	static SDL_Rect camera;

	void monitoring();

private:
	int cnt=0;
	SDL_Window* window;
	// SDL_Renderer* renderer;


};
