#include "game.h"

#include <string>

#include "button.h"
#include "bird.h"
#include "obstacle.h"
#include "background.h"
#include "collision.h"
#include "config.h"

namespace game
{
	enum class Options
	{
		Resume,
		Menu,
		Last
	};
	const int maxButtons = static_cast<int>(Options::Last);

	button::Button buttons[maxButtons];

	bool isMultiplayer = true;

	bool isPaused = false;

	screen::Type nextScreen;

	bool hasScored = false;
	int score = 0;

	Texture2D birdTexture;

	bird::Bird bird1;
	bird::Bird bird2;
	obstacle::Obstacle obstacle;

	static void updateBird(bird::Bird& bird,int jumpKey);
	static void updateObstacle();

	void init(bool multiplayer)
	{
		shape::Rectangle shape;
		shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		shape.size = { 50, 10 };
		float separation = 5;

		buttons[static_cast<int>(Options::Resume)] = button::init(shape, "Resume");
		shape.position.y += shape.size.y + separation;

		buttons[static_cast<int>(Options::Menu)] = button::init(shape, "Menu");
		shape.position.y += shape.size.y + separation;

		isMultiplayer = multiplayer;

		isPaused = false;

		nextScreen = screen::Type::Game;

		hasScored = false;
		score = 0;

		birdTexture = LoadTexture("res/sprites/Ufo.png");

		bird1 = bird::init(birdTexture);
		if (isMultiplayer){
			bird2 = bird::init(birdTexture);
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
			isPaused = !isPaused;
		}

		if (isPaused)
		{
			if (button::update(buttons[static_cast<int>(Options::Resume)])) {
				isPaused = false;
			}
			if (button::update(buttons[static_cast<int>(Options::Menu)])) {
				nextScreen = screen::Type::Menu;
				score = 0;
				isPaused = false;
			}
			return nextScreen;
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

		std::string scoreText = "Score: ";
		scoreText.append(std::to_string(score));
		DrawText(scoreText.c_str(), static_cast<int>(config::res.x)/2, static_cast<int>(config::res.y)/12,25,WHITE);
		
		if (isPaused) {
			DrawRectangle(0,0, static_cast<int>(config::res.x), static_cast<int>(config::res.y), { 112, 31, 126, 128 });
			std::string pausedText = "Paused";
			DrawText(pausedText.c_str(), static_cast<int>(config::res.x)/4, static_cast<int>(config::res.y)/4,125,WHITE);
			for (int i = 0; i < maxButtons; i++)
			{
				button::draw(buttons[i]);
			}
		}
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

		if (!hasScored && bird1.collision.position.x > obstacle.topCollision.position.x) {
			score++;
			hasScored = true;
		}

		if (obstacle.topCollision.position.x + obstacle.topCollision.size.x / 2 < 0)
		{
			obstacle::resetPosition(obstacle);
			hasScored = false;
		}
	}
}