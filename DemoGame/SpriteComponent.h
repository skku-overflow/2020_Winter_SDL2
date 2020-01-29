#pragma once

#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		position = &entity->getComponent<PositionComponent>();

		srcRect = { 0,0,400,400 };
		destRect.w = destRect.h = 32;
	}

	void update() override {
		destRect.x = position->getx();
		destRect.y = position->gety();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};