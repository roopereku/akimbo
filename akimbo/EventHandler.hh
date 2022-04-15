#ifndef AKIMBO_EVENT_HANDLER_HH
#define AKIMBO_EVENT_HANDLER_HH

#include "KeyboardState.hh"
#include "Vector2.hh"

#include <functional>

namespace Akimbo {

class EventHandler
{
public:
	std::function <void(Vec2i position, int button)> onMouseClick;
	std::function <void(KeyboardState& keys)> onKeyPress;
	std::function <void(Vec2i newSize)> onWindowResize;
	std::function <void()> onWindowClose;

	void toggleTextInput();
	void update();

private:
	bool textInput = false;
	KeyboardState keys;
};

}

#endif
