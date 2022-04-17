#ifndef AKIMBO_KEYBOARD_STATE_HH
#define AKIMBO_KEYBOARD_STATE_HH

#include <unordered_map>
#include <array>

namespace Akimbo {

enum class Key
{
	ArrowUp,
	ArrowDown,
	ArrowLeft,
	ArrowRight,

	Alt,
	Shift,
	Control,
};

class KeyboardState
{
public:
	bool isPressed(Key key);
	bool isPressed(char key);

	friend class EventHandler;

protected:
	//	TODO extend to unicode
	std::array <bool, 95> keys;
	std::array <bool, 4> modifierKeys;
	std::array <bool, 4> arrowKeys;
};

}

#endif
