#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	char* path = new char[30];
	   
	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
		tileRect = { x,y,w,h };
		tileID = id;

		switch (tileID) {
		case 0:
			strcpy(path, "images/dirt.png"); 
			break;
		case 1:
			strcpy(path, "images/water.png");
			break;
		case 2:
			strcpy(path, "images/grass.png");
			break;
		default:
			break;
		}
	}

	void init() override {
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}


};