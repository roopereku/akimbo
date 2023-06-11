#ifndef AKIMBO_UI_BUTTON_HH
#define AKIMBO_UI_BUTTON_HH

#include <akimbo/ui/Widget.hh>

#include <functional>

namespace Akimbo
{

namespace UI
{

class Button : public Widget
{
public:
	void onMouseClick(Vec2);
	std::function <void(Button& button)> onClick;
};

}

}

#endif
