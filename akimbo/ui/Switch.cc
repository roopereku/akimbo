#include "Switch.hh"

namespace Akimbo::UI {

Switch::Switch(Core* core, const EdgeConstraints& edges, bool on)
	: Widget(core, edges), on(on)
{
	separatorProgress = 1.0f * on;
}

void Switch::onRender(Frame& frame)
{
	float separatorWidth = size.x / 2;
	float separatorPosition = position.x + (size.x * (separatorProgress / 2));

	frame.color(0, 100, 0);
	frame.drawBox(position, Vec2(separatorPosition - position.x, size.y), true);

	frame.color(100, 100, 100);
	frame.drawBox(Vec2(separatorPosition, position.y), Vec2(position.x + size.x - separatorPosition, size.y), true);

	frame.color(255, 255, 255);
	frame.drawBox(Vec2(separatorPosition, position.y), Vec2(separatorWidth, size.y), true);
}

void Switch::onMouseClick(Vec2 at, int button)
{
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
}

}
