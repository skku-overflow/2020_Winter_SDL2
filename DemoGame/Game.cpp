#include <iostream>
#include "Headers/Game.h"
#include "Headers/TextureManager.h"
#include "Headers/Map.h"
#include "Headers/Vector2D.h"
#include "Headers/Collision.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapfile = "images/terrain_ss.png";

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

//auto& tile0(manager.addEntity());
//auto& tile1(manager.addEntity());
//auto& tile2(manager.addEntity());

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

	//map = new Map();

	Map::LoadMap("images/map.map",25,20);

	player.addComponent<TransformComponent>(296,117,420,420,0.1);
	player.addComponent<SpriteComponent>("images/creeper_idle.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	/*enemy.addComponent<TransformComponent>(500, 500,420,420,0.1);
	enemy.addComponent<SpriteComponent>("images/enemy.png");
	enemy.addComponent<P2_KeyboardController>();
	enemy.addComponent<ColliderComponent>("enemy");
	enemy.addGroup(groupEnemies);*/


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
	monitoring();

	// map->LoadMap();		// pass in the config, external txt, xml, etc. to the LoadMap() if we have map
	manager.refresh();
	manager.update();

	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles) {
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}

	// vector change
	// player.getComponent<TransformComponent>().position.Add(Vector2D(2, 0));

	// custom
	if (Collision::boxInterrupt(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider)) {
		std::cout << "PLAYER Wall hit!" << std::endl;
		player.getComponent<TransformComponent>().velocity * -1;
	}
	if (Collision::boxInterrupt(enemy.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider)) {
		std::cout << "ENEMY Wall hit!" << std::endl;
		enemy.getComponent<TransformComponent>().velocity * -1;
	}

	if (player.getComponent<TransformComponent>().position.x > 500 ||
		Collision::boxInterrupt(player.getComponent<ColliderComponent>().collider,
			wall.getComponent<ColliderComponent>().collider)) {
		player.getComponent<SpriteComponent>().setTex("images/enemy.png");
	}
	else
		player.getComponent<SpriteComponent>().setTex("images/creeper_idle.png");

}

void Game::render() {
	SDL_RenderClear(renderer);
	
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game quit" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
	tile.addGroup(groupMap);
}


void Game::monitoring() {
	cnt++;
	if (!(cnt % 100)) {
		std::cout << "[frame] " << cnt << std::endl;

		std::cout << "player: (" << player.getComponent<TransformComponent>().position.x << ", " <<
			player.getComponent<TransformComponent>().position.y << ")" << std::endl;
	}
	// destR = { 2*cnt,cnt,32,32 };

}