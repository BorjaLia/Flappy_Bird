#include "credits.h"

#include "config.h"
#include "button.h"
#include "label.h"

namespace credits
{
	screen::Type nextScreen;

	enum class Labels
	{
		Title,
		ProgTitle,
		ProgName1,
		ProgName2,
		Last,
	};
	const int maxLabels = static_cast<int>(Labels::Last);
	label::Label labels[maxLabels];

	button::Button exit;

	void init()
	{
		nextScreen = screen::Type::Credits;

		shape::Rectangle shape;
		shape.position = { 10, 10 };
		shape.size = { 12, 12 };

		labels[static_cast<int>(Labels::Title)] = label::init("Credits", shape, render::TextAlign::Left, WHITE);

		shape.position.x = config::gamespace.x - 10;
		shape.size = { 8, 8 };
		exit = button::init(shape, "X");

		shape.size = { 7, 7 };
		shape.position = { 10, 30 };
		labels[static_cast<int>(Labels::ProgTitle)] = label::init("Programmers", shape, render::TextAlign::Left, WHITE);

		shape.position.x = config::gamespace.x - 10;
		labels[static_cast<int>(Labels::ProgName1)] = label::init("Santino Verrua", shape, render::TextAlign::Right, WHITE);

		shape.position.y += 10;
		labels[static_cast<int>(Labels::ProgName2)] = label::init("Borja Lia", shape, render::TextAlign::Right, WHITE);
	}

	screen::Type update()
	{
		if (button::update(exit) || IsKeyPressed(KEY_ESCAPE))
			nextScreen = screen::Type::Menu;

		return nextScreen;
	}

	void draw()
	{
		for (int i = 0; i < maxLabels; i++)
			label::draw(labels[i]);
		button::draw(exit);
	}
}