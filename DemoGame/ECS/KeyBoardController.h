#pragma once

#include "../Headers/Game.h"
#include "ECS.h"
#include "Components.h"

using namespace std;

class SystemController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		cout << "System Controller started" << endl;
	}

	void update() override {
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}
};

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1;
				if (sprite->animated)
					sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				if (sprite->animated)
					sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				if (sprite->animated)
					sprite->Play("Walk");
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				if (sprite->animated)
					sprite->Play("Walk");
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0;
				if (sprite->animated)
					sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				if (sprite->animated)
					sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				if (sprite->animated)
					sprite->Play("Idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				if (sprite->animated)
					sprite->Play("Idle");
			default:
				break;
			}
		}
	}
};


class P2_KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
				transform->velocity.y = -1;
				if (sprite->animated)
					sprite->Play("Walk");
				break;
			case SDLK_LEFT:
				transform->velocity.x = -1;
				if (sprite->animated)
					sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_DOWN:
				transform->velocity.y = 1;
				if (sprite->animated)
					sprite->Play("Walk");
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 1;
				if (sprite->animated)
					sprite->Play("Walk");
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
				transform->velocity.y = 0;
				if (sprite->animated)
					sprite->Play("Idle");
				break;
			case SDLK_LEFT:
				transform->velocity.x = 0;
				if (sprite->animated)
					sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_DOWN:
				transform->velocity.y = 0;
				if (sprite->animated)
					sprite->Play("Idle");
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				if (sprite->animated)
					sprite->Play("Idle");
			default:
				break;
			}
		}
	}
};