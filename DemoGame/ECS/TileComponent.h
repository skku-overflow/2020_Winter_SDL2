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

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {
		texture = TextureManager::LoadTexture(path);
		position.x = xpos;
		position.y = ypos;

		srcRect = { srcX, srcY, 32, 32 };
		destRect = { xpos, ypos, 64, 64 };
	}

	void update() override {
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};