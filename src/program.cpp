#include "program.h"

#include <iostream>
#include <ctime>

#include "render.h"
#include "game.h"
#include "menu.h"
#include "credits.h"

namespace program
{
	static void init();
	static void update();
	static void changeScreen();
	static void draw();
	static void close();

	bool multiplayer = false;

	screen::Type currentScreen = screen::Type::Null;
	screen::Type previousScreen = screen::Type::Null;
		
	void run()
	{
		init();

		while (!WindowShouldClose() && currentScreen != screen::Type::Null)
		{
			update();
			draw();
		}

		close();
	}

	static void init()
	{
		srand(static_cast<int>(time(0)));
		render::startWindow();
		SetExitKey(KEY_NULL);

		currentScreen = screen::Type::Menu;
	}

	static void update()
	{
		switch (currentScreen)
		{
		case screen::Type::Menu:
			currentScreen = menu::update(multiplayer);
			break;
		case screen::Type::Game:
			currentScreen = game::update();
			break;
		case screen::Type::Credits:
			currentScreen = credits::update();
			break;
		}

		if (currentScreen != previousScreen) {
			changeScreen();
		}
	}

	static void changeScreen()
	{
		switch (currentScreen)
		{
		case screen::Type::Menu:
			menu::init();
			break;
		case screen::Type::Game:
			game::init(multiplayer);
			break;
		case screen::Type::Credits:
			credits::init();
			break;
		}

		previousScreen = currentScreen;
	}

	static void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		switch (currentScreen)
		{
		case screen::Type::Menu:
			menu::draw();
			break;
		case screen::Type::Game:
			game::draw();
			break;
		case screen::Type::Credits:
			credits::draw();
			break;
		}

		EndDrawing();
	}

	static void close()
	{
		render::closeWindow();
	}
}