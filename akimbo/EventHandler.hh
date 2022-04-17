#ifndef AKIMBO_EVENT_HANDLER_HH
#define AKIMBO_EVENT_HANDLER_HH

#include "KeyboardState.hh"
#include "Vector2.hh"

#include <functional>

namespace Akimbo {

class EventHandler
{
public:
	EventHandler();

	std::function <void(Vec2i position, int button)> onMouseClick;
	std::function <void(Vec2i newSize)> onWindowResize;
	std::function <void()> onWindowClose;

	std::function <void(char key)> onKeyPress;
	std::function <void(Key key)> onKeyPressOther;

	void update();

private:
	KeyboardState keys;
};

}

#endif
