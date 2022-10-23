#include "Switch.hh"
#include "../Debug.hh"

namespace Akimbo::UI {

Switch::Switch(bool on)
	: on(on)
{
	separatorProgress = 1.0f * on;
}

void Switch::onRender(Render& render)
{
	float separatorPosition = view.topLeft.x + (view.radius.x * separatorProgress);
	Vec2 half = view.radius * Vec2(1, 2);

	render.color(0.0f, 0.7f, 0.0f);
	render.box(view.topLeft, half, true);

	render.color(0.7f, 0.7f, 0.7f);
	render.box(Vec2(0.0f, -1.0f), half, true);

	render.color(1.0f, 1.0f, 1.0f);
	render.box(Vec2(separatorPosition, -1.0f), half, true);
}

void Switch::onMouseClick(Vec2 at, int button)
{
	(void)button;
	(void)at;

	direction = on ? -5 : +5;
	on = !on;

	if(onSwitch)
		onSwitch(on);
}

void Switch::onUpdate(double delta)
{
	//	No movement inside the switch
	if(direction == 0)
		return;

	separatorProgress += static_cast <float> (direction) * delta;
	if(separatorProgress < 0.0f || separatorProgress > 1.0f)
	{
		separatorProgress = 1.0f * on;
		direction = 0;
	}

	render();
}

}
