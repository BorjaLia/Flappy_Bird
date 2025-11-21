#include "collision.h"

namespace coll
{
	bool rectRect(shape::Rectangle rect1, shape::Rectangle rect2)
	{
		return rect1.position.x + rect1.size.x / 2 > rect2.position.x - rect2.size.x / 2 &&
			rect1.position.x - rect1.size.x / 2 < rect2.position.x + rect2.size.x / 2 &&
			rect1.position.y + rect1.size.y / 2 > rect2.position.y - rect2.size.y / 2 &&
			rect1.position.y - rect1.size.y / 2 < rect2.position.y + rect2.size.y / 2;
	}

	bool rectRoof(shape::Rectangle rect, float roof)
	{
		return rect.position.y - rect.size.y / 2 < roof;
	}

	bool rectFloor(shape::Rectangle rect, float floor)
	{
		return rect.position.y + rect.size.y / 2 > floor;
	}

	bool pointRectangle(Vector2 point, shape::Rectangle rectangle)
	{
		return (point.x < rectangle.position.x + rectangle.size.x / 2 &&
			point.x > rectangle.position.x - rectangle.size.x / 2 &&
			point.y < rectangle.position.y + rectangle.size.y / 2 &&
			point.y > rectangle.position.y - rectangle.size.y / 2);
	}
}