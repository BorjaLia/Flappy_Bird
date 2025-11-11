#include "bird.h"

#include "config.h"
#include "render.h"

namespace bird
{
	static void fall(Bird& bird);

	const float jumpStrength = 1.0f;
	const float gravity = 3.0f;

	Bird init()
	{
		Bird bird;
		
		bird.collision.position = { 20, config::gamespace.y / 2 };
		bird.collision.size = { 8, 8 };
		bird.direction = 0.0f;
		bird.speed = 100;

		return bird;
	}

	void move(Bird& bird)
	{
		bird.collision.position.y += bird.direction * bird.speed * GetFrameTime();
		fall(bird);
	}

	void jump(Bird& bird)
	{
		bird.direction = -jumpStrength;
	}

	void bumpRoof(Bird& bird)
	{
		bird.collision.position.y = bird.collision.size.y / 2;
		bird.direction = 0;
	}

	void draw(Bird bird, Color color)
	{
		render::rectangle(bird.collision, color);
	}

	static void fall(Bird& bird)
	{
		bird.direction += gravity * GetFrameTime();
	}
}