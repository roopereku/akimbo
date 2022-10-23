#ifndef AKIMBO_VIEW_HH
#define AKIMBO_VIEW_HH

#include "Vector2.hh"

namespace Akimbo {

class View
{
public:
	View(float horizontalRadius) :
		topLeft(-horizontalRadius, -1.0f), radius(horizontalRadius, 1.0f),
		left(-horizontalRadius), top(-1.0f)
	{
	}

	Vec2 topLeft;
	Vec2 radius;

	float left;
	float top;
};

}

#endif
