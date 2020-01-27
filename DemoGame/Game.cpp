#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

using namespace std;

/* Creating every object without object class */
// SDL_Texture* playerTex;
// SDL_Rect srcR, destR;

// Creating object with object class
GameObject* player;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int width, int height, bool fullscreen) {
	
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems initialized..." << endl;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window)
			cout << "Window created..." << endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created..." << endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	/* Creating texture and rendering without LoadTexture() */
	// SDL_Surface* tmpSurface = IMG_Load("../images/creeper.png");
	// playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	// SDL_FreeSurface(tmpSurface);
	
	/* Creating ... with LoadTexture() but without class */
	// playerTex = TextureManager::LoadTexture("../images/creeper.png", renderer);

	player = new GameObject("../images/creeper.png", 0, 0);
	map = new Map();
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	
	default:
		break;
	}
}

void Game::update() {
	cnt++;
	cout << "[cnt] " << cnt << endl;
	// destR = { 2*cnt,cnt,32,32 };

	player->update();
	// map->LoadMap();		// pass in the config, external txt, xml, etc. to the LoadMap() if we have map
}

void Game::render() {
	SDL_RenderClear(renderer);
	// SDL_RenderCopy(renderer, playerTex,NULL,&destR);
	map->DrawMap();
	player->render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game quit" << endl;
}
