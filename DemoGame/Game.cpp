#include <iostream>
#include "Headers/Game.h"
#include "Headers/TextureManager.h"
#include "Headers/Map.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Headers/Vector2D.h"

using namespace std;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());

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

	map = new Map();

	player.addComponent<TransformComponent>(296,117);
	player.addComponent<SpriteComponent>("images/creeper.png");
	player.addComponent<KeyboardController>();

	enemy.addComponent<TransformComponent>(500, 500);
	enemy.addComponent<SpriteComponent>("images/enemy.png");
	enemy.addComponent<KeyboardController>();
}

void Game::handleEvents() {

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


	// map->LoadMap();		// pass in the config, external txt, xml, etc. to the LoadMap() if we have map
	manager.refresh();
	manager.update();

	cout << "player: (" << player.getComponent<TransformComponent>().position.x << ", " <<
		player.getComponent<TransformComponent>().position.y << ")" << endl;

	player.getComponent<TransformComponent>().position.Add(Vector2D(0,0));

	if (player.getComponent<TransformComponent>().position.x > 500) {
		player.getComponent<SpriteComponent>().setTex("images/enemy.png");
	}
	else 
		player.getComponent<SpriteComponent>().setTex("images/creeper.png");
}

void Game::render() {
	SDL_RenderClear(renderer);
	// SDL_RenderCopy(renderer, playerTex,NULL,&destR);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game quit" << endl;
}
