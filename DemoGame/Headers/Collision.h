#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision {
public:
	static bool boxInterrupt(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool boxInterrupt(const ColliderComponent& colA, const ColliderComponent& colB);
};