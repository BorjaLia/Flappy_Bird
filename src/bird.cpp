#include "bird.h"

#include "config.h"
#include "render.h"
#include <iostream>

namespace bird
{
	static void fall(Bird& bird);

	const float jumpStrength = 1.0f;
	const float gravity = 3.0f;

	Bird init(Texture2D texture,Sound jumpSound,Sound crashSound,Sound fallenSound,Sound topSound, Sound scoreSound)
	{
		Bird bird;
		
		bird.collision.position = { 20, config::gamespace.y / 2 };
		bird.collision.size = { 8, 8 };
		bird.direction = 0.0f;
		bird.speed = 100;

		bird.texture = texture;

		bird.jumpSound = jumpSound;
		bird.crashSound = crashSound;
		bird.fallenSound = fallenSound;
		bird.topSound = topSound;
		bird.scoreSound = scoreSound;

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
		bird.hasJumped = true;
	}

	void bumpRoof(Bird& bird)
	{
		bird.collision.position.y = bird.collision.size.y / 2;
		bird.direction = 0;
		bird.hasTopped = true;
	}

	void draw(Bird bird)
	{
		//render::rectangle(bird.collision, color);
		shape::Rectangle spriteRec = bird.collision;
		spriteRec.size.x *= 3;
		spriteRec.size.y *= 2;
		render::sprite(bird.texture, spriteRec,0.0f);
	}

	void sound(Bird& bird)
	{
		if (bird.hasJumped) {
			bird.hasJumped = false;
			//PlaySound(bird.jumpSound);
			render::sound(bird.jumpSound);
			std::cout << "jumed sound\n";
		}
		if (bird.hasCrashed) {
			bird.hasCrashed = false;
			//PlaySound(bird.crashSound);
			render::sound(bird.crashSound);
			std::cout << "crashed sound\n";
		}
		if (bird.hasFallen) {
			bird.hasFallen = false;
			//PlaySound(bird.fallenSound);
			render::sound(bird.fallenSound);
			std::cout << "fallen sound\n";
		}
		if (bird.hasTopped) {
			bird.hasTopped = false;
			//PlaySound(bird.topSound);
			render::sound(bird.topSound);
			std::cout << "top sound\n";
		}
		if (bird.hasScored) {
			bird.hasScored = false;
			//PlaySound(bird.topSound);
			render::sound(bird.scoreSound);
			std::cout << "score sound\n";
		}
	}

	static void fall(Bird& bird)
	{
		bird.direction += gravity * GetFrameTime();
	}
}