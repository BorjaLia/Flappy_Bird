#pragma once
#include "screens.h"

namespace menu
{
	void init();
	screen::Type update(bool& multiplayer);
	void draw();
}