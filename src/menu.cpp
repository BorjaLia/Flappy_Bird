#include "menu.h"

#include "config.h"
#include "button.h"
#include "label.h"

namespace menu
{
	screen::Type nextScreen;

	enum class Options
	{
		Singleplayer,
		Multiplayer,
		Credits,
		Exit,
		Last
	};
	const int maxButtons = static_cast<int>(Options::Last);

	button::Button buttons[maxButtons];

	label::Label versionLabel;

	void init()
	{
		nextScreen = screen::Type::Menu;

		shape::Rectangle shape;
		shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		shape.size = { 50, 10 };
		float separation = 5;

		buttons[static_cast<int>(Options::Singleplayer)] = button::init(shape, "1 Player");
		shape.position.y += shape.size.y + separation;

		buttons[static_cast<int>(Options::Multiplayer)] = button::init(shape, "2 Player");
		shape.position.y += shape.size.y + separation;

		buttons[static_cast<int>(Options::Credits)] = button::init(shape, "Credits");
		shape.position.y += shape.size.y + separation;

		buttons[static_cast<int>(Options::Exit)] = button::init(shape, "Exit");

		versionLabel = label::init("version 0.4", { {5, 95},{5, 5} }, render::TextAlign::Left, WHITE);
	}

	screen::Type update(bool& multiplayer)
	{
		if (buttons[static_cast<int>(Options::Singleplayer)].isSelected) {
			render::text("P1: W", { buttons[static_cast<int>(Options::Singleplayer)].shape.position.x + buttons[static_cast<int>(Options::Singleplayer)].shape.size.x / 1.5f,buttons[static_cast<int>(Options::Singleplayer)].shape.position.y }, buttons[static_cast<int>(Options::Singleplayer)].shape.size.y /2, WHITE);
		}
		if (buttons[static_cast<int>(Options::Multiplayer)].isSelected) {
			render::text("P1: W	 P2: ^", { buttons[static_cast<int>(Options::Multiplayer)].shape.position.x + buttons[static_cast<int>(Options::Multiplayer)].shape.size.x / 1.25f,buttons[static_cast<int>(Options::Multiplayer)].shape.position.y }, buttons[static_cast<int>(Options::Multiplayer)].shape.size.y / 2, WHITE);
		}
		if (button::update(buttons[static_cast<int>(Options::Singleplayer)])) {
			nextScreen = screen::Type::Game;
			multiplayer = false;
		}
		if (button::update(buttons[static_cast<int>(Options::Multiplayer)])) {
			nextScreen = screen::Type::Game;
			multiplayer = true;
		}
		if (button::update(buttons[static_cast<int>(Options::Credits)])) {
			nextScreen = screen::Type::Credits;
		}
		if (button::update(buttons[static_cast<int>(Options::Exit)])) {
			nextScreen = screen::Type::Null;
		}

		return nextScreen;
	}

	void draw()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			button::draw(buttons[i]);
		}

		label::draw(versionLabel);
	}
}