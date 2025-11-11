#pragma once
#include "shapes.h"

namespace bird
{
	struct Bird
	{
		shape::Rectangle collision;
		float direction;
		int speed;
	};

	Bird init();

	void move(Bird& bird);
	void jump(Bird& bird);
	void bumpRoof(Bird& bird);

	void draw(Bird bird, Color color);
}