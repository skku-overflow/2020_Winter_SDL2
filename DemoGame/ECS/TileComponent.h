#pragma once
#include "ECS.h"
#include "../Headers/Game.h"
#include "SDL.h"

class TileComponent : public Component {
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {
		texture = TextureManager::LoadTexture(path);

		srcRect = { srcX, srcY, 32, 32 };
		destRect = { xpos, ypos, 32, 32 };
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};