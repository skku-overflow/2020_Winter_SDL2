//#pragma once
//#include "Components.h"
// 
//class TransformComponent : public Component {
//private:
//	int xpos;
//	int ypos;
//
//public:
//
//	TransformComponent() {
//		xpos = ypos = 0;
//	}
//
//	TransformComponent(int x, int y) {
//		xpos = x;
//		ypos = y;
//	}
//
//	int getx() { return xpos; }
//	int gety() { return ypos; }
//
//	void setx(int x) { xpos = x; }
//	void sety(int y) { ypos = y; }
//
//	void init() override {
//		cout << "Initialized Position Component" << endl;
//	}
//
//	void update() override {
//		xpos++;
//		ypos++;
//	}
//	
//	void setPos(int x, int y) {
//		xpos = x;
//		ypos = y;
//	}
//};