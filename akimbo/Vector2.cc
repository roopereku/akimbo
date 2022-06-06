#include "Vector2.hh"

bool operator>=(const Vec2& first, const Vec2& second)
{
	return first.x >= second.x && first.y >= second.y;
}

bool operator<=(const Vec2& first, const Vec2& second)
{
	return first.x <= second.x && first.y <= second.y;
}

bool operator>(const Vec2& first, const Vec2& second)
{
	return first.x > second.x && first.y > second.y;
}

bool operator<(const Vec2& first, const Vec2& second)
{
	return first.x < second.x && first.y < second.y;
}
