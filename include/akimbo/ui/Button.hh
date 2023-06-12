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
	bool onMouseClick(Vec2i) override;
	std::function <void(Button& button)> onClick;
};

}

}

#endif
