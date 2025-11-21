#pragma once
#include "shapes.h"

namespace bird
{

	struct Bird
	{
		shape::Rectangle collision;
		Texture2D texture;
		float direction;
		int speed;
	};

	Bird init(Texture2D texture);

	void move(Bird& bird);
	void jump(Bird& bird);
	void bumpRoof(Bird& bird);

	void draw(Bird bird);
}