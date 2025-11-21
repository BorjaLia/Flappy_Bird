#pragma once
#include "shapes.h"

namespace bird
{

	struct Bird
	{
		shape::Rectangle collision;
		Texture2D texture = {};
		float direction;
		int speed;

		bool hasJumped = false;
		Sound jumpSound = {};

		bool hasCrashed = false;
		Sound crashSound = {};

		bool hasFallen = false;
		Sound fallenSound = {};

		bool hasTopped = false;
		Sound topSound = {};

		bool hasScored = false;
		Sound scoreSound = {};
	};

	Bird init(Texture2D texture, Sound jumpSound, Sound crashSound, Sound fallenSound, Sound topSound, Sound scoreSound);

	void move(Bird& bird);
	void jump(Bird& bird);
	void bumpRoof(Bird& bird);

	void draw(Bird bird);

	void sound(Bird& bird);
}