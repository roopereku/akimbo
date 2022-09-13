#ifndef AKIMBO_UI_BUTTON_HH
#define AKIMBO_UI_BUTTON_HH

#include "Widget.hh"
#include "Label.hh"

#include <functional>

namespace Akimbo::UI {

class Button : public Label
{
public:
	Button(Font& font);
	Button();

	void onMouseClick(Vec2, int button) override;
	std::function <void()> onClick;
};

}

#endif
