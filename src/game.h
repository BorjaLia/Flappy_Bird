#pragma once
#include "screens.h"

namespace game
{
	void init(bool multiplayer);
	screen::Type update();
	void draw();
}