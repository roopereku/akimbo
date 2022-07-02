#include "Switch.hh"
#include "../Debug.hh"

namespace Akimbo::UI {

Switch::Switch(Core* core, const EdgeConstraints& edges, bool on)
	: Widget(core, edges), on(on)
{
	separatorProgress = 1.0f * on;
}

void Switch::onRender(Render& frame)
{
	float separatorPosition = frame.topLeft.x + (frame.radius.x * separatorProgress);
	Vec2 half = frame.radius * Vec2(1, 2);

	frame.color(0.0f, 0.7f, 0.0f);
	frame.box(frame.topLeft, half, true);

	frame.color(0.7f, 0.7f, 0.7f);
	frame.box(Vec2(frame.center.x, frame.topLeft.y), half, true);

	frame.color(1.0f, 1.0f, 1.0f);
	frame.box(Vec2(separatorPosition, frame.topLeft.y), half, true);
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
