#pragma once
#include "shapes.h"

namespace obstacle
{
	struct Obstacle
	{
		Vector2 position;
		Texture2D texture;
		shape::Rectangle topCollision;
		shape::Rectangle bottomCollision;
	};

	Obstacle init(Texture2D texture);

	void move(Obstacle& obstacle);
	void resetPosition(Obstacle& obstacle);

	void draw(Obstacle obstacle);
}
