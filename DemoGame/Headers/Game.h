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

	static SDL_Renderer* renderer;
	static SDL_Event event;
	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders
	};

	static bool isRunning;
	static SDL_Rect camera;

	void monitoring();

private:
	int cnt=0;
	SDL_Window* window;
	// SDL_Renderer* renderer;


};
