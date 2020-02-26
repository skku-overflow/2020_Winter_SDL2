#include <iostream>
#include "Headers/Game.h"
#include "Headers/TextureManager.h"
#include "Headers/Map.h"
#include "Headers/Vector2D.h"
#include "Headers/Collision.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"

Map* imap;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

bool Game::isRunning = false;

auto& SYSTEM_MENU(manager.addEntity());
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
// auto& wall(manager.addEntity());

// const char* mapfile = "images/terrain_ss.png";

//auto& tile0(manager.addEntity());
//auto& tile1(manager.addEntity());
//auto& tile2(manager.addEntity());


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

	imap = new Map("images/terrain_ss.png",3,32);

	imap->readMapFile("images/map.map",25,20);
	cout << "|||||||||||||||||||||||||||" << endl;
	imap->LoadMap();

	SYSTEM_MENU.addComponent<SystemController>();

	player.addComponent<TransformComponent>(600,500,420,420,0.1);
	player.addComponent<SpriteComponent>("images/creeper_idle.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	//enemy.addComponent<TransformComponent>(500, 500,420,420,0.1);					// Enemy Components
	//enemy.addComponent<SpriteComponent>("images/enemy.png");
	//enemy.addComponent<P2_KeyboardController>();
	//enemy.addComponent<ColliderComponent>("enemy");
	//enemy.addGroup(groupEnemies);

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& terrains(manager.getGroup(Game::groupTerrain));
auto& enemies(manager.getGroup(Game::groupEnemies));

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

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	//imap->mapRandomize();
	
	manager.refresh();
	manager.update();
	//imap->LoadMap();		// pass in the config, external txt, xml, etc. to the LoadMap() if we have map

	for (auto& c : terrains) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::boxInterrupt(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - camera.w/2;
	camera.y = player.getComponent<TransformComponent>().position.y - camera.h/2;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w*(imap->getMapScale() - 1))
		camera.x = camera.w*(imap->getMapScale() - 1);
	if (camera.y > camera.h*(imap->getMapScale() - 1))
		camera.y = camera.h*(imap->getMapScale() - 1);

	//imap->mapRandomize();

	// Tilemap scrolling
	/*Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles) {
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}*/

	// vector change
	// player.getComponent<TransformComponent>().position.Add(Vector2D(2, 0));

	// Collision detection
	//if (Collision::boxInterrupt(player.getComponent<ColliderComponent>().collider,		// ERROR Trigger
	//	wall.getComponent<ColliderComponent>().collider)) {
	//	std::cout << "PLAYER Wall hit!" << std::endl;
	//	player.getComponent<TransformComponent>().velocity * -1;
	//}
}

void Game::render() {
	SDL_RenderClear(renderer);
	
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& c : terrains) {
		c->draw();
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

void Game::monitoring() {
	cnt++;
	if (!(cnt % 100)) {
		std::cout << "[frame] " << cnt << std::endl;

		std::cout << "player: (" << player.getComponent<TransformComponent>().position.x << ", " <<
			player.getComponent<TransformComponent>().position.y << ")" << std::endl;
	}
	// destR = { 2*cnt,cnt,32,32 };

}