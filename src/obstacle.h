#pragma once
#include "shapes.h"

namespace obstacle
{
	struct Obstacle
	{
		Vector2 position;
		shape::Rectangle topCollision;
		shape::Rectangle bottomCollision;
	};

	Obstacle init();

	void move(Obstacle& obstacle);
	void resetPosition(Obstacle& obstacle);

	void draw(Obstacle obstacle);
}
