#include "Headers/Collision.h"
#include "ECS/ColliderComponent.h"
#include <iostream>

using namespace std;

bool Collision::boxInterrupt(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y) {
		return true;
	}

	return false;
}

bool Collision::boxInterrupt(const ColliderComponent& colA, const ColliderComponent& colB) {
	if (boxInterrupt(colA.collider, colB.collider)) {
		cout << colA.tag << " hit : " << colB.tag << endl;
		return true;
	}
	else
		return false;
}#pragma once
