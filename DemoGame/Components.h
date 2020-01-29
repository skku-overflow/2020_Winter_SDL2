#pragma once
#include "ECS.h"

class PositionComponent : public Component {
private:
	int xpos;
	int ypos;

public:
	int getx() { return xpos; }
	int gety() { return ypos; }

	void init() override {
		xpos = 0;
		ypos = 0;
	}

	void update() override {
		xpos++;
		ypos++;
	}


	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
};