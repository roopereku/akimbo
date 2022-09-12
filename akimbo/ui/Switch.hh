#ifndef AKIMBO_UI_SWITCH_HH
#define AKIMBO_UI_SWITCH_HH

#include "Widget.hh"

#include <functional>

namespace Akimbo::UI {

class Switch : public Widget
{
public:
	Switch(bool on = false);

	void onRender(Render& render) override;
	void onMouseClick(Vec2 at, int button) override;
	void onUpdate(double delta) override;

	std::function <void(bool on)> onSwitch;

private:
	float separatorProgress;
	int direction = 0;
	bool on;
};

}

#endif
