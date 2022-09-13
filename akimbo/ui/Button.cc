#include "Button.hh"

namespace Akimbo::UI {

Button::Button(Font& font) : Label(font) {}
Button::Button() {}

void Button::onMouseClick(Vec2, int button)
{
	if(onClick)
		onClick();
}

}
