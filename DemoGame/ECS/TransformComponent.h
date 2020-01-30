#pragma once
#include "Components.h"
#include "../Headers/Vector2D.h"
#define DEFAULT 3

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int speed = DEFAULT;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void init() override {
		cout << "Initialized Position Component" << endl;

		velocity.setVector(0,0);
	}

	void update() override {
		position.x += velocity.x* speed;
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