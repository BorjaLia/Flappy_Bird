#include "background.h"
#include "render.h"
#include "random.h"
#include "config.h"

namespace background
{
	static Texture2D bgTexture;

	static shape::Rectangle layer1;
	static Texture2D layer1Sprite;
	static shape::Rectangle layer2;
	static Texture2D layer2Sprite;
	static shape::Rectangle layer3;
	static Texture2D layer3Sprite;

	void init()
	{
		bgTexture = LoadTexture("res/sprites/background.png");

		layer1Sprite = LoadTexture("res/sprites/one.png");
		layer2Sprite = LoadTexture("res/sprites/two.png");
		layer3Sprite = LoadTexture("res/sprites/three.png");

		layer1.size = { 100,100  };
		layer1.position = { 100, config::gamespace.y - layer1.size.y / 2 };

		layer2.size = { 70, 70 };
		layer2.position = { 100, config::gamespace.y - layer2.size.y / 2 };

		layer3.size = { 70,45 };
		layer3.position = { 100, config::gamespace.y - layer3.size.y / 2 };

	}

	void update()
	{
		layer1.position.x -= 10 * GetFrameTime();
		if (layer1.position.x + layer1.size.x / 2 < 0)
			layer1.position.x = config::gamespace.x + layer1.size.x;

		layer2.position.x -= 15 * GetFrameTime();
		if (layer2.position.x + layer2.size.x / 2 < 0)
			layer2.position.x = config::gamespace.x + layer2.size.x;

		layer3.position.x -= 25 * GetFrameTime();
		if (layer3.position.x + layer3.size.x / 2 < 0)
			layer3.position.x = config::gamespace.x + layer3.size.x;
	}

	void draw()
	{
		shape::Rectangle bgRec;

		bgRec.position.x = config::gamespace.x / 2;
		bgRec.position.y = config::gamespace.y / 2;

		bgRec.size = { 160,100 };

		render::sprite(bgTexture,bgRec,0.0f);

		//render::rectangle(layer1, BLUE);
		//render::rectangle(layer2, YELLOW);
		//render::rectangle(layer3, GREEN);
		
		render::sprite(layer1Sprite,layer1,0.0f);
		render::sprite(layer2Sprite,layer2,0.0f);
		render::sprite(layer3Sprite,layer3,0.0f);
	}
}