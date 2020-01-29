#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
private:
	int xpos;
	int ypos;

public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;
	int speed = 3;

	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(int sc)
	{
		position.x = 0.0f;
		position.y = 0.0f;
		scale = sc;
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	int x() { return xpos; }
	int y() { return ypos; }
	void x(int x) { xpos = x; }
	void y(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y; }

	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};