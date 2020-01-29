#pragma once
#include "Components.h"
#include "../Headers/Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.x = y;
	}

	void init() override {
		cout << "Initialized Position Component" << endl;
	}

	void update() override {
		
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