#pragma once

#include "Components.h"
#include "TransformComponent.h"
#include "../Headers/TextureManager.h"
#include "SDL.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);

	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect = { 0,0,transform->width, transform->height };
		// destRect.w = destRect.h = 32;
	}

	void update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};