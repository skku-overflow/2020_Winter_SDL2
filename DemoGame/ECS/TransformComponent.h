#pragma once
#include "Components.h"
#include "../Headers/Vector2D.h"
#define DEFAULT 3

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	float scale = 1;

	int speed = DEFAULT;


	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int sc) {
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.Zero();
	}

	TransformComponent(float x, float y, float sc) {
		position.x = x;
		position.y = y;
		scale = sc;
	}

	TransformComponent(float x, float y, int w, int h, float sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		cout << "Initialized Position Component" << endl;

		velocity.Zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	

	//int getx() { return xpos; }
	//int gety() { return ypos; }
	//void setx(int x) { xpos = x; }
	//void sety(int y) { ypos = y; }
	//void setPos(int x, int y) {
	//	xpos = x;
	//	ypos = y;
	//}
};