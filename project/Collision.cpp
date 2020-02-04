#include "Collision.h"
#include "ColliderComponent.h"
#include <iostream>
using namespace std;

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.w >= recA.y)
	{ return true; }
	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (Collision::AABB(colA.collider, colB.collider))
	{
		cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}