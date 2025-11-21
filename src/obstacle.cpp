#include "obstacle.h"

#include "config.h"
#include "render.h"
#include "random.h"

namespace obstacle
{
	static void fixCollisionsPosition(Obstacle& obstacle);

	const int speed = 50;
	const int spaceToPass = 30;

	Obstacle init()
	{
		Obstacle obstacle;

		obstacle.position = { config::gamespace.x + 5, config::gamespace.y / 2 };

		obstacle.topCollision.size = { 15, 60 };
		obstacle.bottomCollision.size = { 15, 60 };

		fixCollisionsPosition(obstacle);

		return obstacle;
	}

	void move(Obstacle& obstacle)
	{
		obstacle.position.x -= speed * GetFrameTime();
		fixCollisionsPosition(obstacle);
	}

	void resetPosition(Obstacle& obstacle)
	{
		obstacle.position.x = config::gamespace.x + 5;
		obstacle.position.y = static_cast<float>(random::intRange(25, static_cast<int>(config::gamespace.y - 25)));

		fixCollisionsPosition(obstacle);
	}

	static void fixCollisionsPosition(Obstacle& obstacle)
	{
		obstacle.topCollision.position.x = obstacle.position.x;
		obstacle.topCollision.position.y = obstacle.position.y - (spaceToPass / 2) - (obstacle.topCollision.size.y / 2);

		obstacle.bottomCollision.position.x = obstacle.position.x;
		obstacle.bottomCollision.position.y = obstacle.position.y + (spaceToPass / 2) + (obstacle.bottomCollision.size.y / 2);
	}

	void draw(Obstacle obstacle)
	{
		render::rectangle(obstacle.topCollision, RED);
		render::rectangle(obstacle.bottomCollision, RED);
	}
}