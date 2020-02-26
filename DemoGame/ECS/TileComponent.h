#pragma once
#include "ECS.h"
#include "../Headers/Game.h"
#include "SDL.h"

class TileComponent : public Component {
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int tsX, int tsY, int epX, int epY, int tileSize, int mapScale, const char* path) {
		texture = TextureManager::LoadTexture(path);
		position.x = epX*tileSize*mapScale;
		position.y = epY*tileSize*mapScale;

		srcRect = { tsX*tileSize, tsY*tileSize, tileSize, tileSize };
		destRect = { epX*tileSize, epY*tileSize, tileSize * mapScale, tileSize * mapScale };
	}

	void update() override {
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};