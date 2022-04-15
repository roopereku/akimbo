#ifndef AKIMBO_KEYBOARD_STATE_HH
#define AKIMBO_KEYBOARD_STATE_HH

#include <unordered_map>
#include <array>

namespace Akimbo {

enum class Modifier
{
	Shift, Control,
	Alt, AltGr
};

enum class Arrow
{
	Left, Right, Top, Down
};

class KeyboardState
{
public:
	bool isPressed(Modifier modifier);
	bool isPressed(Arrow arrowKey);
	bool isPressed(char key);

	char key();

	friend class EventHandler;

protected:
	char lastKey;

	//	TODO extend to unicode
	std::array <bool, 95> keys;
	std::array <bool, 4> modifierKeys;
	std::array <bool, 4> arrowKeys;
};

}

#endif
