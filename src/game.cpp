#include "game.h"

#include "bird.h"
#include "obstacle.h"
#include "background.h"
#include "collision.h"
#include "config.h"

namespace game
{
	bool isMultiplayer = true;

	screen::Type nextScreen;

	bird::Bird bird1;
	bird::Bird bird2;
	obstacle::Obstacle obstacle;

	static void updateBird(bird::Bird& bird,int jumpKey);
	static void updateObstacle();

	void init(bool multiplayer)
	{
		isMultiplayer = multiplayer;

		nextScreen = screen::Type::Game;

		bird1 = bird::init();
		if (isMultiplayer){
			bird2 = bird::init();
			bird1.collision.position.x -= 5;
			bird2.collision.position.x += 5;
		}
		obstacle = obstacle::init();

		background::init();
	}

	screen::Type update()
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			nextScreen = screen::Type::Menu;
		}
		updateBird(bird1,KEY_W);
		if (isMultiplayer) {
			updateBird(bird2,KEY_UP);
		}
		updateObstacle();
		background::update();

		return nextScreen;
	}

	void draw()
	{
		background::draw();
		bird::draw(bird1, WHITE);
		if (isMultiplayer) {
			bird::draw(bird2,GRAY);
		}
		obstacle::draw(obstacle);
	}

	static void updateBird(bird::Bird& bird, int jumpKey)
	{
		if (IsKeyPressed(jumpKey)) {
			bird::jump(bird);
		}

		if (coll::rectRect(bird.collision, obstacle.topCollision) || coll::rectRect(bird.collision, obstacle.bottomCollision)) {
			init(isMultiplayer);
		}

		if (coll::rectRoof(bird.collision, 0)) {
			bird::bumpRoof(bird);
		}

		if (coll::rectFloor(bird.collision, config::gamespace.y)) {
			init(isMultiplayer);
		}

		bird::move(bird);
	}

	static void updateObstacle()
	{
		obstacle::move(obstacle);
		if (obstacle.topCollision.position.x + obstacle.topCollision.size.x / 2 < 0)
		{
			obstacle::resetPosition(obstacle);
		}
	}
}